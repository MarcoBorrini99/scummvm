/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "tetraedge/tetraedge.h"
#include "tetraedge/detection.h"
#include "tetraedge/console.h"
#include "common/scummsys.h"
#include "common/config-manager.h"
#include "common/debug-channels.h"
#include "common/events.h"
#include "common/system.h"
#include "common/savefile.h"
#include "engines/util.h"
#include "engines/dialogs.h"
#include "graphics/palette.h"

#include "tetraedge/game/game.h"
#include "tetraedge/game/application.h"
#include "tetraedge/game/character.h"
#include "tetraedge/te/te_core.h"
#include "tetraedge/te/te_renderer.h"
#include "tetraedge/te/te_resource_manager.h"
#include "tetraedge/te/te_sound_manager.h"
#include "tetraedge/te/te_input_mgr.h"

namespace Tetraedge {

TetraedgeEngine *g_engine;

TetraedgeEngine::TetraedgeEngine(OSystem *syst, const ADGameDescription *gameDesc) : Engine(syst),
	_gameDescription(gameDesc), _randomSource("Tetraedge"), _resourceManager(nullptr),
	_core(nullptr),	_application(nullptr), _game(nullptr), _renderer(nullptr),
	_soundManager(nullptr), _inputMgr(nullptr) {
	g_engine = this;
}

TetraedgeEngine::~TetraedgeEngine() {
	delete _core;
	delete _game;
	delete _application;
	delete _renderer;
	delete _soundManager;
	delete _resourceManager;
	delete _inputMgr;
	Object3D::cleanup();
	Character::cleanup();
}

/*static*/
Common::StringArray TetraedgeEngine::splitString (const Common::String &text, char c) {
	Common::StringArray values;

	Common::String str = text;
	size_t pos;
	while ((pos = str.findFirstOf(c)) != Common::String::npos) {
		values.push_back(Common::String(str.c_str(), pos));
		str = Common::String(str.c_str() + pos + 1);
	}

	values.push_back(str);
	return values;
}

Application *TetraedgeEngine::getApplication() {
	// created in run()
	return _application;
}

TeCore *TetraedgeEngine::getCore() {
	if (_core == nullptr)
		_core = new TeCore();
	return _core;
}

Game *TetraedgeEngine::getGame() {
	if (_game == nullptr)
		_game = new Game();
	return _game;
}

TeSoundManager *TetraedgeEngine::getSoundManager() {
	if (_soundManager == nullptr)
		_soundManager = new TeSoundManager();
	return _soundManager;
}

TeRenderer *TetraedgeEngine::getRenderer() {
	// created in run()
	return _renderer;
}

TeResourceManager *TetraedgeEngine::getResourceManager() {
	if (_resourceManager == nullptr)
		_resourceManager = new TeResourceManager();
	return _resourceManager;
}

TeInputMgr *TetraedgeEngine::getInputMgr() {
	if (_inputMgr == nullptr)
		_inputMgr = new TeInputMgr();
	return _inputMgr;
}

uint32 TetraedgeEngine::getFeatures() const {
	return _gameDescription->flags;
}

Common::String TetraedgeEngine::getGameId() const {
	return _gameDescription->gameId;
}

bool TetraedgeEngine::canSaveGameStateCurrently() {
	return canSaveAutosaveCurrently() && !_application->isLockCursor();
}

bool TetraedgeEngine::canSaveAutosaveCurrently() {
	return _game && _application && _game->running()
		&& !_game->currentScene().empty() && !_game->currentZone().empty();
}

Common::Error TetraedgeEngine::loadGameState(int slot) {
	// In case autosaves are on, do a save first before loading the new save
	saveAutosaveIfEnabled();

	Common::String saveStateName = getSaveStateName(slot);

	Common::InSaveFile *saveFile = getSaveFileManager()->openForLoading(saveStateName);

	if (!saveFile)
		return Common::kReadingFailed;

	// The game will reopen the file and do the loading, see Game::initLoadedBackupData
	getGame()->setLoadName(saveStateName);

	delete saveFile;
	return Common::kNoError;
}

Common::Error TetraedgeEngine::loadGameStream(Common::SeekableReadStream *stream) {
	Common::Serializer s(stream, nullptr);
	Common::Error retval = syncGame(s);
	return retval;
}

void TetraedgeEngine::configureSearchPaths() {
	const Common::FSNode gameDataDir(ConfMan.get("path"));
	SearchMan.addSubDirectoryMatching(gameDataDir, "Resources", 0, 5);
}

int TetraedgeEngine::getDefaultScreenWidth() const {
	return 800;
}

int TetraedgeEngine::getDefaultScreenHeight() const {
	return 600;
}

bool TetraedgeEngine::onKeyUp(const Common::KeyState &state) {
	if (state.keycode == Common::KEYCODE_l) {
		if (loadGameDialog())
			_game->initLoadedBackupData();
	} else if (state.keycode == Common::KEYCODE_s) {
		saveGameDialog();
	}

	return false;
}

Common::Error TetraedgeEngine::run() {
	initGraphics3d(getDefaultScreenWidth(), getDefaultScreenHeight());

	configureSearchPaths();
	// from BasicOpenGLView::prepareOpenGL..
	_application = new Application();
	_renderer = new TeRenderer();
	_renderer->init();
	_renderer->reset();

	// Set the engine's debugger console
	setDebugger(new Console());

	getInputMgr()->_keyUpSignal.add(this, &TetraedgeEngine::onKeyUp);

	// If a savegame was selected from the launcher, load it.
	// Should be before application->create() because it only
	// sets the game name to load inside the Game object.  It will
	// actually be loaded when the application is created.
	int saveSlot = ConfMan.getInt("save_slot");
	if (saveSlot != -1)
		(void)loadGameState(saveSlot);

	_application->create();

	Common::Event e;

	while (!shouldQuit()) {
		while (g_system->getEventManager()->pollEvent(e)) {
			getInputMgr()->handleEvent(e);
		}

		_application->run();

		g_system->delayMillis(10);
	}

	return Common::kNoError;
}

Common::Error TetraedgeEngine::syncGame(Common::Serializer &s) {
	return getGame()->syncGame(s);
}

void TetraedgeEngine::openConfigDialog() {
	GUI::ConfigDialog dlg;
	dlg.runModal();

	g_system->applyBackendSettings();
	applyGameSettings();
	syncSoundSettings();
}

/*static*/
void TetraedgeEngine::getSavegameThumbnail(Graphics::Surface &thumb) {
	g_engine->getApplication()->getSavegameThumbnail(thumb);
}


} // namespace Tetraedge
