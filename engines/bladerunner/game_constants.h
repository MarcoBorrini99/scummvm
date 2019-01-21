/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef BLADERUNNER_GAME_CONSTANTS_H
#define BLADERUNNER_GAME_CONSTANTS_H

namespace BladeRunner {

enum Actors {
	kActorMcCoy = 0,
	kActorSteele = 1,
	kActorGordo = 2,
	kActorDektora = 3,
	kActorGuzza = 4,
	kActorClovis = 5,
	kActorLucy = 6,
	kActorIzo = 7,
	kActorSadik = 8,
	kActorCrazylegs = 9,
	kActorLuther = 10,
	kActorGrigorian = 11,
	kActorTransient = 12,
	kActorLance = 13,
	kActorBulletBob = 14,
	kActorRunciter = 15,
	kActorInsectDealer = 16,
	kActorTyrellGuard = 17,
	kActorEarlyQ = 18,
	kActorZuben = 19,
	kActorHasan = 20,
	kActorMarcus = 21,
	kActorMia = 22,
	kActorOfficerLeary = 23,
	kActorOfficerGrayford = 24,
	kActorHanoi = 25,
	kActorBaker = 26,
	kActorDeskClerk = 27,
	kActorHowieLee = 28,
	kActorFishDealer = 29,
	kActorKlein = 30,
	kActorMurray = 31,
	kActorHawkersBarkeep = 32,
	kActorHolloway = 33,
	kActorSergeantWalls = 34,
	kActorMoraji = 35,
	kActorTheBard = 36,
	kActorPhotographer = 37,
	kActorDispatcher = 38,
	kActorAnsweringMachine = 39,
	kActorRajif = 40,
	kActorGovernorKolvig = 41,
	kActorEarlyQBartender = 42,
	kActorHawkersParrot = 43,
	kActorTaffyPatron = 44,
	kActorLockupGuard = 45,
	kActorTeenager = 46,
	kActorHysteriaPatron1 = 47,
	kActorHysteriaPatron2 = 48,
	kActorHysteriaPatron3 = 49,
	kActorShoeshineMan = 50,
	kActorTyrell = 51,
	kActorChew = 52,
	kActorGaff = 53,
	kActorBryant = 54,
	kActorTaffy = 55,
	kActorSebastian = 56,
	kActorRachael = 57,
	kActorGeneralDoll = 58,
	kActorIsabella = 59,
	kActorBlimpGuy = 60,
	kActorNewscaster = 61,
	kActorLeon = 62,
	kActorMaleAnnouncer = 63,
	kActorFreeSlotA = 64,
	kActorFreeSlotB = 65,
	kActorMaggie = 66,
	kActorGenwalkerA = 67,
	kActorGenwalkerB = 68,
	kActorGenwalkerC = 69,
	kActorMutant1 = 70,
	kActorMutant2 = 71,
	kActorMutant3 = 72,
	kActorVoiceOver = 99
};

enum Clues {
	kClueOfficersStatement = 0,
	kClueDoorForced1 = 1,
	kClueDoorForced2 = 2,
	kClueLimpingFootprints = 3,
	kClueGracefulFootprints = 4,
	kClueShellCasings = 5,
	kClueCandy = 6,
	kClueToyDog = 7,
	kClueChopstickWrapper = 8,
	kClueSushiMenu = 9,
	kClueLabCorpses = 10,
	kClueLabShellCasings = 11,
	kClueRuncitersVideo = 12,
	kClueLucy = 13,
	kClueDragonflyAnklet = 14,
	kClueReferenceLetter = 15,
	kClueCrowdInterviewA = 16,
	kClueCrowdInterviewB = 17,
	kClueZubenRunsAway = 18,
	kClueZubenInterview = 19,
	kClueZuben = 20,
	kClueBigManLimping = 21,
	kClueRunciterInterviewA = 22,
	kClueRunciterInterviewB1 = 23,
	kClueRunciterInterviewB2 = 24,
	kClueHowieLeeInterview = 25,
	kCluePaintTransfer = 26,
	kClueChromeDebris = 27,
	kClueRuncitersViewA = 28,
	kClueRuncitersViewB = 29,
	kClueCarColorAndMake = 30,
	kCluePartialLicenseNumber = 31,
	kClueBriefcase = 32,
	kClueGaffsInformation = 33,
	kClueCrystalVisitedRunciters = 34,
	kClueCrystalVisitedChinatown = 35,
	kClueWantedPoster = 36,
	kClueLicensePlate = 37,
	kClueLicensePlateMatch = 38,
	kClueLabPaintTransfer = 39,
	kClueDispatchHitAndRun = 40, // is never acquired
	kClueInceptShotRoy = 41,
	kClueInceptShotsLeon = 42,
	kCluePhoneCallGuzza = 43,
	kClueDragonflyEarring = 44,
	kClueTyrellSecurity = 45,
	kClueTyrellGuardInterview = 46,
	kClueBombingSuspect = 47,
	kClueSadiksGun = 48,
	kClueDetonatorWire = 49,
	kClueVictimInformation = 50,
	kClueAttemptedFileAccess = 51,
	kClueCrystalsCase = 52,
	kClueKingstonKitchenBox1 = 53,
	kClueTyrellSalesPamphlet1 = 54,
	kClueTyrellSalesPamphlet2 = 55,
	kCluePeruvianLadyInterview = 56,
	kClueHasanInterview = 57,
	kClueBobInterview1 = 58,
	kClueBobInterview2 = 59,
	kClueIzoInterview = 60,
	kClueIzosWarning = 61,
	kClueRadiationGoggles = 62,
	kClueGogglesReplicantIssue = 63,
	kClueFishLadyInterview = 64,
	kClueDogCollar1 = 65,
	kClueWeaponsCache = 66,
	kClueChewInterview = 67,
	kClueMorajiInterview = 68,
	kClueGordoInterview1 = 69,
	kClueGordoInterview2 = 70,
	kClueAnsweringMachineMessage = 71,
	kClueChessTable = 72,
	kClueSightingSadikBradbury = 73,
	kClueStaggeredbyPunches = 74,
	kClueMaggieBracelet = 75,
	kClueEnvelope = 76,
	kClueIzosFriend = 77,
	kClueChinaBarSecurityPhoto = 78,
	kCluePurchasedScorpions = 79,
	kClueWeaponsOrderForm = 80,
	kClueShippingForm = 81,
	kClueGuzzasCash = 82,
	kCluePoliceIssueWeapons = 83,
	kClueHysteriaToken = 84,
	kClueRagDoll = 85,
	kClueMoonbus1 = 86,
	kClueCheese = 87,
	kClueDektorasDressingRoom = 88,
	kClueEarlyQsClub = 89,
	kClueDragonflyCollection = 90,
	kClueDragonflyBelt = 91,
	kClueEarlyQInterview = 92,
	kClueStrangeScale1 = 93,
	kClueDektoraInterview1 = 94,
	kClueSuspectDektora = 95,
	kClueDektoraInterview2 = 96,
	kClueDektoraInterview3 = 97,
	kClueDektorasCard = 98,
	kClueGrigoriansNote = 99,
	kClueCollectionReceipt = 100,
	kClueSpecialIngredient = 101,
	kClueStolenCheese = 102,
	kClueGordoInterview3 = 103,
	kClueGordoConfession = 104,
	kClueGordosLighter1 = 105,
	kClueGordosLighter2 = 106,
	kClueDektoraInterview4 = 107,
	kClueHollowayInterview = 108,
	kClueBakersBadge = 109,
	kClueHoldensBadge = 110,
	kClueCar = 111,
	kClueCarIdentified = 112,
	kClueCarRegistration1 = 113,
	kClueCarRegistration2 = 114,
	kClueCarRegistration3 = 115,
	kClueCrazylegsInterview1 = 116,
	kClueCrazylegsInterview2 = 117,
	kClueLichenDogWrapper = 118,
	kClueRequisitionForm = 119,
	kClueScaryChair = 120,
	kClueIzosStashRaided = 121,
	kClueHomelessManInterview1 = 122,
	kClueHomelessManInterview2 = 123,
	kClueHomelessManKid = 124,
	kClueFolder = 125,
	kClueGuzzaFramedMcCoy = 126,
	kClueOriginalShippingForm = 127,
	kClueOriginalRequisitionForm = 128,
	kClueCandyWrapper = 129,
	kClueGordoBlabs = 130,
	kClueFlaskOfAbsinthe = 131,
	kClueGuzzaAgreesToMeet = 132,
	kClueDektoraConfession = 133,
	kClueRunciterConfession1 = 134,
	kClueRunciterConfession2 = 135,
	kClueLutherLanceInterview = 136,
	kClueMoonbus2 = 137,
	kClueMoonbusCloseup = 138,
	kCluePhoneCallDektora1 = 139,
	kCluePhoneCallDektora2 = 140,
	kCluePhoneCallLucy1 = 141,
	kCluePhoneCallLucy2 = 142,
	kCluePhoneCallClovis = 143,
	kCluePhoneCallCrystal = 144,
	kCluePowerSource = 145,
	kClueBomb = 146,
	kClueDNATyrell = 147,
	kClueDNASebastian = 148,
	kClueDNAChew = 149,
	kClueDNAMoraji = 150,
	kClueDNALutherLance = 151,
	kClueDNAMarcus = 152,
	kClueGarterSnake = 153,
	kClueSlug = 154,
	kClueGoldfish = 155,
	kClueZubenTalksAboutLucy1 = 156,
	kClueZubenTalksAboutLucy2 = 157,
	kClueZubensMotive = 158,
	kClueSightingBulletBob = 159,
	kClueSightingClovis = 160,
	kClueSightingDektora = 161,
	kClueVKDektoraReplicant = 162,
	kClueVKDektoraHuman = 163,
	kClueVKBobGorskyReplicant = 164,
	kClueVKBobGorskyHuman = 165,
	kClueVKLutherLanceReplicant = 166,
	kClueVKLutherLanceHuman = 167,
	kClueVKGrigorianReplicant = 168,
	kClueVKGrigorianHuman = 169,
	kClueVKIzoReplicant = 170,
	kClueVKIzoHuman = 171,
	kClueVKCrazylegsReplicant = 172,
	kClueVKCrazylegsHuman = 173,
	kClueVKRunciterReplicant = 174,
	kClueVKRunciterHuman = 175,
	kClueVKEarlyQReplicant = 176,
	kClueVKEarlyQHuman = 177,
	kClueCrimeSceneNotes = 178,
	kClueGrigorianInterviewA = 179,
	kClueGrigorianInterviewB1 = 180,
	kClueGrigorianInterviewB2 = 181,
	kClueLabAnalysisGoldChain = 182,
	kClueSightingZuben = 183,
	kClueCrystalRetiredZuben = 184,
	kClueCrystalRetiredGordo = 185,
	kClueSightingGordo = 186,
	kClueCrystalRetiredIzo = 187,
	kClueClovisIncept = 188,
	kClueDektoraIncept = 189,
	kClueLucyIncept = 190,
	kClueGordoIncept = 191,
	kClueIzoIncept = 192,
	kClueSadikIncept = 193,
	kClueZubenIncept = 194,
	kClueMcCoyIncept = 195,
	kClueWarRecordsGordoFrizz = 196,
	kCluePoliceWeaponUsed = 197,
	kClueMcCoysWeaponUsedonBob = 198,
	kClueBobRobbed = 199,
	kClueBobShotInSelfDefense = 200,
	kClueBobShotInColdBlood = 201,
	kClueMcCoyRecoveredHoldensBadge = 202,
	kClueCrystalTestedBulletBob = 203,
	kClueCrystalRetiredBob = 204,
	kClueCrystalTestedCrazylegs = 205,
	kClueCrystalRetiredCrazylegs = 206,
	kClueCrystalArrestedCrazylegs = 207,
	kClueCrystalTestedRunciter = 208,
	kClueCrystalRetiredRunciter1 = 209,
	kClueCrystalRetiredRunciter2 = 210,
	kClueSightingMcCoyRuncitersShop = 211,
	kClueMcCoyKilledRunciter1 = 212,
	kClueMcCoysDescription = 213,
	kClueMcCoyIsABladeRunner = 214,
	kClueMcCoyLetZubenEscape = 215,
	kClueMcCoyWarnedIzo = 216,
	kClueMcCoyHelpedIzoIzoIsAReplicant = 217,
	kClueMcCoyHelpedDektora = 218,
	kClueMcCoyHelpedLucy = 219,
	kClueMcCoyHelpedGordo = 220,
	kClueMcCoyShotGuzza = 221,
	kClueMcCoyRetiredZuben = 222,
	kClueMcCoyRetiredLucy = 223,
	kClueMcCoyRetiredDektora = 224,
	kClueMcCoyRetiredGordo = 225,
	kClueMcCoyRetiredSadik = 226,
	kClueMcCoyShotZubenInTheBack = 227,
	kClueMcCoyRetiredLutherLance = 228,
	kClueMcCoyBetrayal = 229,
	kClueMcCoyKilledRunciter2 = 230,
	kClueClovisOrdersMcCoysDeath = 231,
	kClueEarlyAttemptedToSeduceLucy = 232,
	kClueCarWasStolen = 233,
	kClueGrigoriansResponse1 = 234,
	kClueGrigoriansResponse2 = 235,
	kClueCrazysInvolvement = 236,
	kClueGrigoriansResources = 237,
	kClueMcCoyPulledAGun = 238,
	kClueMcCoyIsStupid = 239,
	kClueMcCoyIsAnnoying = 240,
	kClueMcCoyIsKind = 241,
	kClueMcCoyIsInsane = 242,
	kClueAnimalMurderSuspect = 243,
	kClueMilitaryBoots = 244,
	kClueOuterDressingRoom = 245,
	kCluePhotoOfMcCoy1 = 246,
	kCluePhotoOfMcCoy2 = 247,
	kClueEarlyQAndLucy = 248,
	kClueClovisflowers = 249,
	kClueLucyWithDektora = 250,
	kClueWomanInAnimoidRow = 251,
	kClueScorpions = 252,
	kClueStrangeScale2 = 253,
	kClueChinaBarSecurityCamera = 254,
	kClueIzo = 255,
	kClueGuzza = 256,
	kClueChinaBarSecurityDisc = 257,
	kClueScorpionbox = 258,
	kClueTyrellSecurityPhoto = 259,
	kClueChinaBar = 260,
	kCluePlasticExplosive = 261,
	kClueDogCollar2 = 262,
	kClueKingstonKitchenBox2 = 263,
	kClueCrystalsCigarette = 264,
	kClueSpinnerKeys = 265,
	kClueAct2Ended = 266,
	kClueAct3Ended = 267,
	kClueAct4Ended = 268,
	kClueExpertBomber = 269,
	kClueAmateurBomber = 270,
	kClueVKLucyReplicant = 271,
	kClueVKLucyHuman = 272,
	kClueLucyInterview = 273,
	kClueMoonbusReflection = 274,
	kClueMcCoyAtMoonbus = 275,
	kClueClovisAtMoonbus = 276,
	kClueSadikAtMoonbus = 277,
	kClueRachaelInterview = 278,
	kClueTyrellInterview = 279,
	kClueRuncitersConfession1 = 280,
	kClueRuncitersConfession2 = 281,
	kClueRuncitersConfession3 = 282,
	kClueEarlyInterviewA = 283,
	kClueEarlyInterviewB1 = 284,
	kClueEarlyInterviewB2 = 285,
	kClueCrazylegsInterview3 = 286,
	kClueCrazylegGgrovels = 287
};

enum ClueTypes {
	kClueTypeIntangible = -1,
	kClueTypePhotograph = 0,
	kClueTypeVideoClip = 1,
	kClueTypeAudioRecording = 2,
	kClueTypeObject = 3
};

enum Suspects {
	kSuspectSadik = 0,
	kSuspectClovis = 1,
	kSuspectZuben = 2,
	kSuspectLucy = 3,
	kSuspectDekora = 4,
	kSuspectGordo = 5,
	kSuspectIzo = 6,
	kSuspectMcCoy = 7,
	kSuspectGuzza = 8
};

enum Crimes {
	kCrimeAnimalMurder = 0,
	kCrimeEisendullerMurder = 1,
	kCrimeArmsDealing = 2,
	kCrimeMorajiMurder = 3,
	kCrimeBradburyAssault = 4,
	kCrimeFactoryBombing = 5,
	kCrimeBobMurder = 6,
	kCrimeRunciterMurder = 7,
	kCrimeMoonbusHijacking = 8
};

enum SpinnerDestinations {
	kSpinnerDestinationPoliceStation = 0,
	kSpinnerDestinationMcCoysApartment = 1,
	kSpinnerDestinationRuncitersAnimals = 2,
	kSpinnerDestinationChinatown = 3,
	kSpinnerDestinationAnimoidRow = 4,
	kSpinnerDestinationTyrellBuilding = 5,
	kSpinnerDestinationDNARow = 6,
	kSpinnerDestinationBradburyBuilding = 7,
	kSpinnerDestinationNightclubRow = 8,
	kSpinnerDestinationHysteriaHall = 9
};

enum Flags {
	kFlagNotUsed0 = 0, // is never checked
	kFlagRC02Entered = 1,
	// 2 is never used
	kFlagGotOfficersStatement = 3,
	kFlagRC02FirstLeave = 4,
	// 5 is never used
	kFlagRunciterInterviewA = 6,
	// 7 is never used
	kFlagRC01toRC02 = 8,
	kFlagRC02toRC01 = 9,
	kFlagDR01toDR04 = 10,
	kFlagDR04toDR01 = 11,
	kFlagKleinTalkShellCasings = 12,
	kFlagKleinTalkOfficersStatement = 13,
	kFlagPS10toPS11 = 14,
	kFlagPS11toPS10 = 15,
	kFlagPS11toPS12 = 16,
	kFlagPS12toPS11 = 17, // is never checked
	kFlagPS12toPS13 = 18,
	kFlagPS13toPS12 = 19,
	// 20 is never used
	kFlagPS13toPS05 = 21,
	kFlagPS02toPS05 = 22,
	kFlagPS06toPS05 = 23,
	kFlagIntroPlayed = 24,
	kFlagCT01Visited = 25,
	kFlagCT01McCoyTalkedToHowieLee = 26,
	kFlagCT01Evidence1Linked = 27,
	kFlagCT01Evidence2Linked = 28,
	kFlagCT01ZubenLeft = 29,
	kFlagNotUsed30 = 30,  // is never set
	kFlagCT01ZubenGone = 31,
	kFlagCT01McCoyTalkedToGordo = 32,
	kFlagMA02toMA06 = 33,
	kFlagMA06ToMA02 = 34,
	kFlagMA02ToMA04 = 35,
	kFlagMA04ToMA02 = 36,
	kFlagMA01toMA06 = 37,
	kFlagMA06toMA01 = 38,
	kFlagPS04toPS03 = 39,
	kFlagZubenRetired = 40,
	kFlagZubenSpared = 41,
	kFlagPS03toPS04 = 42,
	kFlagPS15Entered = 43,
	kFlagIzoIsReplicant = 44,
	kFlagGordoIsReplicant = 45,
	kFlagLucyIsReplicant = 46,
	kFlagDektoraIsReplicant = 47,
	kFlagSadikIsReplicant = 48,
	kFlagPS09GrigorianTalk1 = 49,
	// 50 is never used
	kFlagGrigorianDislikeMcCoy = 51,
	// 52 is never used
	kFlagPS09GrigorianDialogue = 53,
	kFlagPS09GrigorianTalk2 = 54,
	kFlagGrigorianArrested = 55,
	kFlagPS09CrazylegsGrigorianTalk = 56,
	kFlagMA07toMA06 = 57,
	kFlagMA06toMA07 = 58,
	kFlagCT02ZubenTalk = 59,
	kFlagMA02MaggieIntroduced = 60,
	kFlagChapter1Ended = 61,
	kFlagMA04toMA05 = 62,
	kFlagMA05toMA04 = 63,
	kFlagGaffApproachedMcCoyAboutZuben = 64,
	// 65 is never used
	// 66 is never used
	// 67 is never used
	kFlagCT02toCT01 = 68,
	kFlagCT02toCT03 = 69,
	kFlagCT03toCT02 = 70,
	kFlagCT03toCT01 = 71,
	kFlagCT03toCT04 = 72,
	kFlagCT04toCT03 = 73,
	kFlagCT04toCT05 = 74,
	kFlagCT05toCT04 = 75,
	kFlagCT05toCT12 = 76,
	kFlagCT05toCT06 = 77,
	kFlagCT06toCT05 = 78,
	kFlagCT06toCT08 = 79,
	kFlagCT08toCT06 = 80, // is never checked
	kFlagCT08toCT09 = 81,
	kFlagCT09toCT10 = 82, // is never checked
	kFlagCT09toCT11 = 83, // is never checked
	kFlagCT09toCT08 = 84, // is never checked
	kFlagCT10toCT09 = 85,
	kFlagCT11toCT12 = 86,
	// 87 is never used
	kFlagCT12toCT01 = 88,
	kFlagCT12toCT03 = 89,
	kFlagCT12toCT05 = 90,
	kFlagCT12toCT11 = 91,
	// 92 is never used
	// 93 is never used
	kFlagWarehouseOpen = 94,
	kFlagTB05toTB02 = 95,
	kFlagTB02toTB05 = 96, // is never checked
	kFlagTB05toTB06 = 97, // is never checked
	kFlagTB06toTB05 = 98,
	kFlagTB05MonitorIntro = 99,
	kFlagTB05MonitorUnlockAttempt = 100,
	kFlagTB05MonitorDone = 101,
	kFlagTB06Visited = 102,
	kFlagNotUsed103 = 103, // is never set
	kFlagKleinTalkPaintTransfer = 104,
	kFlagKleinTalkChromeDebris = 105,
	kFlagIsabellaIntroduced = 106,
	kFlagHC04toRC03 = 107,
	kFlagRC03toHC04 = 108,
	kFlagHC04toHC02 = 109,
	kFlagHC02toHC04 = 110,
	kFlagKleinTalkClues = 111,
	// 112 is never used
	// 113 is never used
	kFlagRC03toRC01 = 114,
	kFlagRC01toRC03 = 115,
	kFlagRC03toAR02 = 116,
	kFlagAR02toRC03 = 117,
	kFlagRC03toUG01 = 118,
	kFlagUG01toRC03 = 119,
	kFlagRC03toRC04 = 120, // is never checked
	kFlagRC04toRC03 = 121,
	// 122 is never used
	kFlagCT01toCT12 = 123,
	// 122 is never used
	kFlagMcCoyHasShellCasings = 125,
	kFlagMcCoyHasOfficersStatement = 126,
	kFlagMcCoyHasPaintTransfer = 127,
	kFlagMcCoyHasChromeDebris = 128,
	kFlagZubenCheckOnMcCoy = 129,
	kFlagPS02toPS01 = 130,
	kFlagPS02toPS07 = 131,
	kFlagPS02toPS03 = 132,
	kFlagPS02toPS09 = 133,
	kFlagPS03toPS14 = 134,
	kFlagPS14toPS03 = 135,
	kFlagPS05toPS06 = 136,
	kFlagHomelessTalkedTo = 137,
	kFlagKleinInsulted = 138,
	// 139 is never used
	// 140 is never used
	kFlagRC51Available = 141,
	kFlagNotUsed142 = 142, // is never checked
	// 143 is never used
	kFlagCT07toCT06 = 144,
	kFlagZubenPhoto = 145,
	kFlagChapter1Ending = 146,
	kFlagChopstickWrapperTaken = 147,
	kFlagCandyTaken = 148,
	kFlagToyDogTaken = 149,
	kFlagNotUsed150 = 150, // has no use
	kFlagRC03UnlockedToUG01 = 151,
	kFlagUG15toUG16 = 152,
	kFlagUG16toUG15 = 153,
	kFlagTB02toTB03 = 154, // is never checked
	kFlagTB03toTB02 = 155,
	kFlagKleinInsultedTalk = 156,
	// 157 is never used
	kFlagSergeantWallsBuzzInDone = 158,
	kFlagGuzzaTalkZubenRetired = 159,
	kFlagGuzzaTalkZubenEscaped = 160,
	kFlagGuzzaTalk1 = 161,
	kFlagGuzzaTalk2 = 162,
	kFlagChromeDebrisTaken = 163,
	kFlagIzoArrested = 164,
	kFlagCrazylegsArrested = 165,
	kFlagPS09CrazylegsTalk1 = 166,
	kFlagPS09IzoTalk1 = 167,
	kFlagPS09IzoTalk2 = 168,
	kFlagMcCoyKilledHomeless = 169,
	kFlagHomelessBodyInDumpster = 170,
	kFlagHomelessBodyFound = 171,
	kFlagDumpsterEmptied = 172,
	kFlagHomelessBodyInDumpsterNotChecked = 173, // is never checked
	kFlagLicensePlaceFound = 174,
	kFlagPS09CrazylegsTalk2 = 175,
	kFlagMcCoyAtCTxx = 176,
	kFlagMcCoyAtDRxx = 177,
	kFlagMcCoyAtPSxx = 178,
	kFlagMcCoyAtMAxx = 179,
	kFlagMcCoyAtARxx = 180,
	kFlagMcCoyAtNRxx = 181,
	kFlagMcCoyAtRCxx = 182,



	kFlagRC01PoliceDone = 186,
	kFlagRC02TalkedToRunciter = 187,
	// 188 is never used
	// 189 is never used
	kFlagShellCasingsTaken = 190,
	// 191 is never used
	kFlagBoughtHowieLeeFood = 192,
	// 193 is never used
	// 194 is never used
	// 195 is never used
	kFlagKleinAnimation1 = 196,
	kFlagKleinAnimation2 = 197,
	kFlagKleinAnimation3 = 198,
	kFlagOfficerLearyTakingNotes = 199,
	// 200 is never used
	// 201 is never used
	// 202 is never used
	// 203 is never used
	kFlagPS15toPS05 = 204,
	// 205 is never used
	kFlagSergeantWallsBuzzInRequest = 206, // is never set
	// 207 is never used
	// 208 is never used
	// 209 is never used
	kFlagCT02ZubenFled = 210,
	kFlagPS09Entered = 211,
	kFlagNotUsed212 = 212, // is never checked
	// 213 is never used
	// 214 is never used
	// 215 is never used
	kFlagBB09toBB10a = 216,
	// 217 is never used
	kFlagBB08toBB09 = 218,
	kFlagBB09toBB08 = 219,
	kFlagBB09toBB10b = 220,
	kFlagBB10toBB09 = 221,
	kFlagBB10toBB11 = 222, // is never checked
	kFlagBB11toBB10 = 223,
	kFlagDR01toDR02 = 224,
	kFlagDR02toDR01 = 225,
	kFlagDR02toDR03 = 226,
	kFlagDR03toDR02 = 227,
	kFlagDR04toDR05 = 228, // is never checked
	kFlagDR05toDR04 = 229,
	kFlagDR04toDR06 = 230,
	kFlagDR06toDR04 = 231,
	kFlagNotUsed232 = 232,
	// 233 is never used
	kFlagCT02toCT01walk = 234,
	// 235 is never used
	kFlagMcCoyAnimation1 = 236,
	// 237 is never used
	// 238 is never used
	kFlagHowieLeeAnimation1 = 239,
	// 240 is never used
	// 241 is never used
	// 242 is never used
	// 243 is never used
	// 244 is never used
	// 245 is never used
	// 246 is never used
	kFlagArrivedFromSpinner1 = 247,
	kFlagSpinnerAtCT01 = 248,
	kFlagSpinnerAtRC01 = 249,
	kFlagSpinnerAtMA01 = 250,
	kFlagSpinnerAtPS01 = 251,
	kFlagSpinnerAtAR01 = 252,
	kFlagSpinnerAtDR01 = 253,
	kFlagSpinnerAtBB01 = 254,
	kFlagSpinnerAtNR01 = 255,
	kFlagSpinnerAtHF01 = 256,
	kFlagMcCoyAtHFxx = 257,
	kFlagMcCoyAtBBxx = 258,
	kFlagMcCoyAtUGxx = 259,
	// 260 is never used
	kFlagMcCoyAtTBxx = 261,
	kFlagBB01toBB02 = 262,
	kFlagBB02toBB01 = 263,
	kFlagBB01toDR02 = 264,
	kFlagDR02toBB01 = 265,
	kFlagMorajiExploded = 266,
	kFlagDR03ChewTalk1 = 267,
	kFlagDR06JesterActive = 268,
	kFlagDR05BombActivated = 269,
	kFlagDR05ChainShot = 270,
	kFlagDR05BombWillExplode = 271,
	kFlagDR05BombExploded = 272,
	kFlagArrivedFromSpinner2 = 273,
	kFlagDR05MorajiTalk = 274,
	// 275 is never used
	kFlagNotUsed276 = 276, // is never set
	// 277 is never used
	kFlagDR06KeyboardChecked = 278,
	// 279 is never used
	kFlagDR06VidphoneChecked = 280,
	kFlagBB03toBB02 = 281,
	kFlagBB02toBB03 = 282, // is never checked
	kFlagBB03toBB04 = 283,
	kFlagBB04toBB03 = 284,
	kFlagBB03toBB05 = 285, // is never checked
	kFlagBB05toBB03 = 286,
	kFlagRC04Entered = 287,
	// 288 is never used
	kFlagRC04McCoyShotBob = 289,
	kFlagRC04BobTalk1 = 290,
	// 291 is never used
	kFlagRC04BobTalk2 = 292,
	kFlagCT02PotTipped = 293,
	kFlagGaffSpinnerCT12 = 294,
	kFlagRC04BobShootMcCoy = 295,
	kFlagRC04McCoyCombatMode = 296,
	kFlagBB05toBB06 = 297,
	kFlagBB06toBB05 = 298,
	kFlagBB05toBB07 = 299,
	kFlagBB07toBB05 = 300,
	kFlagBB05toBB12 = 301, // is never checked
	kFlagBB12toBB05 = 302,
	kFlagRC04McCoyWarned =  303,
	kFlagCT11toCT09 = 304, // is never checked
	kFlagRC04BobTalkAmmo = 305,
	kFlagNotUsed306 = 306, // is never set
	kFlagSpinnerAtTB02 = 307,
	kFlagHF01toHF02 = 308,
	kFlagHF02toHF01 = 309,
	kFlagHF01toHF03 = 310,
	kFlagHF03toHF01 = 311,
	kFlagHF01toHF05 = 312,
	kFlagHF05toHF01 = 313,
	kFlagUG01toUG02 = 314,
	kFlagUG02toUG01 = 315,
	kFlagUG01toUG10 = 316,
	kFlagUG10toUG01 = 317,
	kFlagUG02toHC03 = 318,
	kFlagHC03toUG02 = 319,
	kFlagAR01toAR02 = 320,
	kFlagAR02toAR01 = 321,
	kFlagAR01toHC01 = 322,
	kFlagHC01toAR01 = 323,
	kFlagUG01SteamOff = 324,

	kFlagFishDealerTalk = 328,
	kFlagInsectDealerInterviewed = 329,
	kFlagHassanTalk = 330,
	kFlagScorpionsChecked = 331,

	kFlagInsectDealerTalk = 366,
	kFlagStungByScorpion = 367,

	kFlagNotUsed370 = 370, // is never checked

	kFlagDirectorsCut = 378,

	kFlagHC01toHC02 = 384,
	kFlagHC02toHC01 = 385,
	kFlagHC01toHC03 = 386, // is never checked
	kFlagHC03toHC01 = 387,
	kFlagHC03TrapDoorOpen = 388,
	// 389 is never used
	// 390 is never used

	KFlagMcCoyAndOfficerLearyTalking = 392,

	KFlagMcCoyAndOfficerLearyArtMetaphor = 397,

	kFlagIzoTalk1 = 400,
	kFlagIzoTalk2 = 401,
	kFlagHC03Available = 402,
	kFlagHC03CageOpen = 403,
	kFlagHawkersBarkeepIntroduction = 404,
	kFlagHawkersBarkeepBraceletTalk = 405,

	kFlagUnused407 = 407, // is never checked

	kFlagUG09toCT12 = 432,
	kFlagCT12ToUG09 = 433,
	kFlagGenericWalkerWaiting = 443,
	kFlagIzoShot = 444,

	kFlagUG02WeaponsChecked = 449,
	kFlagTB02ElevatorToTB05 = 450,
	kFlagTB05Entered = 451,
	kFlagTB02GuardTalk1 = 453,
	kFlagTB02GuardTalk2 = 455,
	kFlagTB02SteeleTalk = 456,
	kFlagTB02SteeleEnter = 457,
	kFlagSteeleWalkingAround = 460,
	kFlagMaggieIsHurt = 461,
	kFlagPS04GuzzaLeft = 462,
	kFlagMcCoyArrested = 465,
	kFlagUG10GateOpen = 474,
	kFlagMcCoyAtPS03 = 478, // has no use
	kFlagMcCoyAtHCxx = 479,
	kFlagTB06Introduction = 483,
	kFlagPhotographerToTB06 = 485,
	kFlagDNARowAvailable = 486,
	kFlagKIAPrivacyAddon = 487,
	kFlagCT04HomelessTrashFinish = 492,
	kFlagUG02FromUG01 = 498,
	kFlagUG02Interactive = 499,

	kFlagDR05ExplodedEntered = 511,
	kFlagDR05BombExplosionView = 515,
	kFlagCT07ZubenAttack = 516,
	kFlagTB06DogCollarTaken = 519,
	kFlagTB06KitchenBoxTaken = 520,
	kFlagKIAPrivacyAddonIntro = 599,
	kFlagTB07toTB02 = 608,
	kFlagMcCoySleeping = 647,
	kFlagPhoneMessageFromClovis = 649,
	kFlagPhoneMessageFromLucy = 650,
	kFlagRagiationGooglesTaken = 656,
	kFlagDNARowAvailableTalk = 660,
	kFlagChapter2Intro = 678,
	kFlagPS05TV0 = 688,
	kFlagPS05TV1 = 689,
	kFlagPS05TV2 = 690,
	kFlagPS05TV3 = 691,
	kFlagPS05TV4 = 692,
	kFlagUG03DeadHomeless = 693,
	kFlagRC04Locked = 702,
	kFlagTB06PhotographTalk1 = 707,
	kFlagUG02AmmoTaken = 708,
	kFlagRC51Discovered = 709,
	kFlagAR01Entered = 710,
	kFlagMA04WatchedTV = 711,
	kFlagMcCoyShotAtZuben = 712,
	kFlagRC04BobTalk3 = 717,
	kFlagCT02McCoyFell = 719,
	kFlagCT02McCoyCombatReady = 720,
	kFlagZubenBountyPaid = 723,
	kFlagAR02Entered = 726,
	kFlagPS04WeaponsOrderForm = 727
};

enum Variables {
	kVariableChapter = 1,
	kVariableChinyen = 2,
	kVariablePoliceMazeScore = 9,
	kVariablePoliceMazePS10TargetCounter = 10,
	kVariablePoliceMazePS11TargetCounter = 11,
	kVariablePoliceMazePS12TargetCounter = 12,
	kVariablePoliceMazePS13TargetCounter = 13,
	kVariableMcCoyEvidenceMissed = 14,
	kVariableIzoShot = 19, // has no use
	kVariableBobShot = 24, // has no use
	kVariableGenericWalkerAModel = 32,
	kVariableGenericWalkerBModel = 33,
	kVariableGenericWalkerCModel = 34,
	kVariableWalkLoopActor = 37,
	kVariableWalkLoopRun = 38,
	kVariableMcCoyDrinks = 42, // is never checked
	kVariableAffectionTowards = 45, // 0 none, 1 steele, 2 dektora, 3 lucy
	kVariableDNAEvidences = 48,
	kVariableReplicants = 51,
	kVariableNextTvNews = 52
};

enum Outtakes {
	kOuttakeIntro = 0,
	kOuttakeMovieA = 1,
	kOuttakeMovieB1 = 2,
	kOuttakeMovieB2 = 3,
	kOuttakeMovieB3 = 4,
	kOuttakeMovieB4 = 5,
	kOuttakeMovieB5 = 6,
	kOuttakeMovieC1 = 7,
	kOuttakeMovieC2 = 8,
	kOuttakeMovieC3 = 9,
	kOuttakeMovieD = 10,
	kOuttakeInterrogation = 11,
	kOuttakeEnd1A = 12,
	kOuttakeEnd1B = 13,
	kOuttakeEnd1C = 14,
	kOuttakeEnd1D = 15,
	kOuttakeEnd1E = 16,
	kOuttakeEnd1F = 17,
	kOuttakeEnd2 = 18,
	kOuttakeEnd3 = 19,
	kOuttakeEnd4A = 20,
	kOuttakeEnd4B = 21,
	kOuttakeEnd4C = 22,
	kOuttakeEnd4D = 23,
	kOuttakeEnd5 = 24,
	kOuttakeEnd6 = 25,
	kOuttakeEnd7 = 26,
	kOuttakeTyrellBuildingFly = 27,
	kOuttakeWestwood = 28,
	kOuttakeFlyThrough = 29,
	kOuttakeAway1 = 30,
	kOuttakeAway2 = 31,
	kOuttakeAscent = 32,
	kOuttakeDescent = 33,
	kOuttakeInside1 = 34,
	kOuttakeInside2 = 35,
	kOuttakeTowards1 = 36,
	kOuttakeTowards2 = 37,
	kOuttakeTowards3 = 38,
	kOuttakeRachel = 39,
	kOuttakeDektora = 40,
	kOuttakeBladeRunner = 41
};

enum AnimationModes {
	kAnimationModeIdle = 0,
	kAnimationModeWalk = 1,
	kAnimationModeRun = 2,
	kAnimationModeTalk = 3,
	kAnimationModeCombatIdle = 4,
	kAnimationModeCombatAim = 5,
	kAnimationModeCombatAttack = 6,
	kAnimationModeCombatWalk = 7,
	kAnimationModeCombatRun = 8,
	kAnimationModeHit = 21,
	kAnimationModeCombatHit = 22,
	kAnimationModeSpinnerGetIn = 41,
	kAnimationModeSpinnerGetOut = 42,
	// 43 - taking photo/using cellphone
	kAnimationModeWalkUp = 44,
	kAnimationModeWalkDown = 45,
	kAnimationModeCombatWalkUp = 46,
	kAnimationModeCombatWalkDown = 47,
	kAnimationModeDie = 48,
	kAnimationModeCombatDie = 49,
	kAnimationModeFeeding = 52,
	kAnimationModeSit = 53, // TODO: check
	kAnimationModeClimbUp = 64,
	kAnimationModeClimbDown = 65,
	kAnimationModeCombatClimbUp = 66,
	kAnimationModeCombatClimbDown = 67
};

enum SceneLoopMode {
	kSceneLoopModeNone = -1,
	kSceneLoopModeLoseControl = 0,
	kSceneLoopModeChangeSet = 1,
	kSceneLoopModeOnce = 2,
	kSceneLoopModeSpinner = 3
};

enum Scenes {
	kSceneAR01 = 0,
	kSceneAR02 = 1,
	kSceneBB01 = 2,
	kSceneBB02 = 3,
	kSceneBB03 = 4,
	kSceneBB04 = 5,
	kSceneBB05 = 6,
	kSceneBB06 = 7,
	kSceneBB07 = 8,
	kSceneBB08 = 9,
	kSceneBB09 = 10,
	kSceneBB10 = 11,
	kSceneBB11 = 12,
	kSceneCT01 = 13, // Chinatown - Howie Lee Restaurant
	kSceneCT02 = 14, // Chinatown - Kitchen
	kSceneCT03 = 15, // Chinatown - Back alley
	kSceneCT04 = 16, // Chinatown - Back alley - Dumpster
	kSceneCT05 = 17, // Chinatown - Warehouse - Inside
	kSceneCT06 = 18, // Chinatown - Passage
	kSceneCT07 = 19, // Chinatown - Passage form back
	kSceneCT08 = 20, // Chinatown - Yukon Hotel - Backroom
	kSceneCT09 = 21, // Chinatown - Yukon Hotel - Lobby
	kSceneCT10 = 22, // Chinatown - Yukon Hotel - Room
	kSceneCT11 = 23, // Chinatown - Yukon Hotel - Outside
	kSceneCT12 = 24, // Chinatown - Warehouse - Outside
	kSceneDR01 = 25,
	kSceneDR02 = 26,
	kSceneDR03 = 27,
	kSceneDR04 = 28,
	kSceneDR05 = 29,
	kSceneDR06 = 30,
	kSceneHC01 = 31, // Hawker's circle - Green pawn - Outside
	kSceneHC02 = 32, // Hawker's circle - China bar
	kSceneHC03 = 33, // Hawker's circle - Green pawn - Inside
	kSceneHF01 = 34,
	kSceneHF02 = 35,
	kSceneHF03 = 36,
	kSceneHF04 = 37,
	kSceneHF05 = 38,
	kSceneHF06 = 39,
	kSceneHF07 = 40,
	kSceneKP01 = 41,
	kSceneKP02 = 42,
	kSceneKP03 = 43,
	kSceneKP04 = 44,
	kSceneKP05 = 45,
	kSceneKP06 = 46,
	kSceneKP07 = 47, // Kipple - Moonbus inside
	kSceneMA01 = 48, // McCoy's Apartment - Roof
	kSceneMA02 = 49, // McCoy's Apartment - Living room
	kSceneMA04 = 50, // McCoy's Apartment - Sleeping room
	kSceneMA05 = 51, // McCoy's Apartment - Balcony
	kSceneMA06 = 52, // McCoy's Apartment - Elevator
	kSceneMA07 = 53, // McCoy's Apartment - Ground floor
	kSceneNR01 = 54,
	kSceneNR02 = 55,
	kSceneNR03 = 56,
	kSceneNR04 = 57,
	kSceneNR05 = 58,
	kSceneNR06 = 59,
	kSceneNR07 = 60,
	kSceneNR08 = 61,
	kSceneNR09 = 62,
	kSceneNR10 = 63,
	kSceneNR11 = 64,
	kScenePS01 = 65, // Police Station - Roof
	kScenePS02 = 66, // Police Station - Elevator
	kScenePS03 = 67, // Police Station - Ground floor
	kScenePS04 = 68, // Police Station - Guzza's Office
	kScenePS05 = 69,
	kScenePS06 = 70,
	kScenePS07 = 71,
	kScenePS09 = 72, // Police Station - Lockup
	kScenePS10 = 73,
	kScenePS11 = 74,
	kScenePS12 = 75,
	kScenePS13 = 76,
	kScenePS14 = 77,
	kSceneRC01 = 78, // Runciter - Outside
	kSceneRC02 = 79, // Runciter - Inside
	kSceneRC03 = 80, // Bullet Bob - outside
	kSceneRC04 = 81, // Bullet Bob - inside
	kSceneTB02 = 82, // Tyrell Building - reception
	kSceneTB03 = 83,
	kSceneTB05 = 84, // Tyrell Building - Grav Test Lab - outside
	kSceneTB06 = 85, // Tyrell Building - Grav Test Lab - inside
	kSceneUG01 = 86, // Underground - Under Bullet Bob entrance
	kSceneUG02 = 87, // Underground - Under Green pawn
	kSceneUG03 = 88,
	kSceneUG04 = 89,
	kSceneUG05 = 90,
	kSceneUG06 = 91,
	kSceneUG07 = 92,
	kSceneUG08 = 93,
	kSceneUG09 = 94,
	kSceneUG10 = 95,
	kSceneUG12 = 96,
	kSceneUG13 = 97,
	kSceneUG14 = 98,
	kSceneUG15 = 99,
	kSceneUG16 = 100,
	kSceneUG17 = 101,
	kSceneUG18 = 102,
	kSceneUG19 = 103,
	kSceneBB51 = 104,
	kSceneCT51 = 105,
	kSceneHC04 = 106, // Hawker's circle - Kingston kitchen
	kSceneRC51 = 107, // Runciter - Lucy's desk
	kSceneTB07 = 108,
	kScenePS15 = 119, // Police Station - Armory
	kSceneBB12 = 120
};

enum Sets
{
	kSetAR01_AR02 = 0,
	kSetBB02_BB04_BB06_BB51 = 1,
	kSetBB06_BB07 = 2, //BB06
	kSetBB07 = 3,
	kSetCT01_CT12 = 4,
	kSetCT03_CT04 = 5,
	kSetCT08_CT51_UG12 = 6, //UG12
	kSetDR01_DR02_DR04 = 7,
	kSetHC01_HC02_HC03_HC04 = 8,
	kSetKP05_KP06 = 9,
	kSetMA02_MA04 = 10, //MA04
	kSetNR02 = 11,
	kSetNR04 = 12,
	kSetNR05_NR08 = 13,
	kSetPS10_PS11_PS12_PS13 = 14,
	kSetPS05 = 15,
	kSetRC02_RC51 = 16,
	kSetTB02_TB03 = 17,
	kSetTB07 = 18,
	kSetUG16 = 19,
	kSetBB01 = 20,
	kSetBB03 = 21,
	kSetBB05 = 22,
	kSetBB08 = 23,
	kSetBB09 = 24,
	kSetBB10 = 25,
	kSetBB11 = 26,
	kSetCT02 = 27,
	kSetCT05 = 28,
	kSetCT06 = 29,
	kSetCT07 = 30,
	kSetCT09 = 31,
	kSetCT10 = 32,
	kSetCT11 = 33,
	kSetDR03 = 34,
	kSetDR05 = 35,
	kSetDR06 = 36,
	kSetHF01 = 37,
	kSetHF02 = 38,
	kSetHF03 = 39,
	kSetHF04 = 40,
	kSetHF05 = 41,
	kSetHF06 = 42,
	kSetHF07 = 43,
	kSetKP01 = 44,
	kSetKP02 = 45,
	kSetKP03 = 46,
	kSetKP04 = 47,
	kSetKP07 = 48,
	kSetMA01 = 49,
	kSetMA04 = 50,
	kSetMA05 = 51,
	kSetMA06 = 52,
	kSetMA07 = 53,
	kSetNR01 = 54,
	kSetNR03 = 55,
	kSetNR06 = 56,
	kSetNR07 = 57,
	kSetNR09 = 58,
	kSetNR10 = 59,
	kSetNR11 = 60,
	kSetPS01 = 61,
	kSetPS02 = 62,
	kSetPS03 = 63,
	kSetPS04 = 64,
	kSetPS06 = 65,
	kSetPS07 = 66,
	kSetPS09 = 67,
	kSetPS14 = 68,
	kSetRC01 = 69,
	kSetRC03 = 70,
	kSetRC04 = 71,
	kSetTB05 = 72,
	kSetTB06 = 73,
	kSetUG01 = 74,
	kSetUG02 = 75,
	kSetUG03 = 76,
	kSetUG04 = 77,
	kSetUG05 = 78,
	kSetUG06 = 79,
	kSetUG07 = 80,
	kSetUG08 = 81,
	kSetUG09 = 82,
	kSetUG10 = 83,
	kSetUG12 = 84,
	kSetUG13 = 85,
	kSetUG14 = 86,
	kSetUG15 = 87,
	kSetUG17 = 88,
	kSetUG18 = 89,
	kSetUG19 = 90,
	kSetFreeSlotA = 91,
	kSetFreeSlotB = 92,
	kSetFreeSlotC = 93,
	kSetFreeSlotD = 94,
	kSetFreeSlotE = 95,
	kSetFreeSlotF = 96,
	kSetFreeSlotG = 97,
	kSetFreeSlotH = 98,
	kSetFreeSlotI = 99,
	kSetFreeSlotJ = 100,
	kSetPS15 = 101,
	kSetBB12 = 102
};

enum GameItems {
	kItemPS10Target1 = 0,
	kItemPS10Target2 = 1,
	kItemPS10Target3 = 2,
	kItemPS10Target4 = 3,
	kItemPS10Target5 = 4,
	kItemPS10Target6 = 5,
	kItemPS10Target7 = 6,
	kItemPS10Target8 = 7,
	kItemPS10Target9 = 8,
	kItemPS11Target1 = 9,
	kItemPS11Target2 = 10,
	kItemPS11Target3 = 11,
	kItemPS11Target4 = 12,
	kItemPS11Target5 = 13,
	kItemPS11Target6 = 14,
	kItemPS11Target7 = 15,
	kItemPS11Target8 = 16,
	kItemPS11Target9 = 17,
	kItemPS11Target10 = 18,
	kItemPS11Target11 = 19,
	kItemPS11Target12 = 20,
	kItemPS11Target13 = 21,
	kItemPS11Target14 = 22,
	kItemPS11Target15 = 23,
	// 24 is never used
	// 25 is never used
	// 26 is never used
	kItemPS11Target16 = 27,
	// 28 is never used
	kItemPS12Target1 = 29,
	kItemPS12Target2 = 30,
	kItemPS12Target3 = 31,
	kItemPS12Target4 = 32,
	kItemPS12Target5 = 33,
	kItemPS12Target6 = 34,
	kItemPS12Target7 = 35,
	kItemPS12Target8 = 36,
	kItemPS12Target9 = 37,
	kItemPS12Target10 = 38,
	kItemPS12Target11 = 39,
	kItemPS12Target12 = 40,
	kItemPS12Target13 = 41,
	kItemPS12Target14 = 42,
	kItemPS12Target15 = 43,
	kItemPS12Target16 = 44,
	kItemPS12Target17 = 45,
	kItemPS13Target1 = 46,
	kItemPS13Target2 = 47,
	kItemPS13Target3 = 48,
	kItemPS13Target4 = 49,
	kItemPS13Target5 = 50,
	kItemPS13Target6 = 51,
	kItemPS13Target7 = 52,
	kItemPS13Target8 = 53,
	kItemPS13Target9 = 54,
	kItemPS13Target10 = 55,
	kItemPS13Target11 = 56,
	kItemPS13Target12 = 57,
	kItemPS13Target13 = 58,
	// 59 is never used
	// 60 is never used
	// 61 is never used
	kItemPS13Target14 = 62,
	kItemPS13Target15 = 63,
	// 64 is never used
	// 65 is never used
	kItemChromeDebris = 66,
	// 67 is never used
	// 68 is never used
	// 69 is never used
	// 70 is never used
	// 71 is never used
	// 72 is never used
	// 73 is never used
	// 74 is never used
	// 75 is never used
	// 76 is never used
	kItemDragonflyEarring = 76,
	kItemCandy = 79,
	kItemChopstickWrapper = 82,
	kItemDogCollar = 84,
	kItemRadiationGoogles = 88,
	kItemToyDog = 98,
	kItemShellCasingA = 100,
	kItemShellCasingB = 101,
	kItemShellCasingC = 102,
	kItemDeadDogA = 103,
	kItemDeadDogB = 104,
	kItemDeadDogC = 105,
	kItemScrorpions = 106,
	kItemCamera = 107,
	kItemKitchenBox = 108,
	kItemWeaponsCrate = 110,
	kItemWeaponsOrderForm = 111,
	kItemTyrellSalesPamphlet = 119,
	kItemHC03Lock = 121
};

enum Elevators {
	kElevatorMA = 1,
	kElevatorPS = 2
};

// enum SceneObjectOffset {
// 	kSceneObjectActorIdStart  = 0,
// 	kSceneObjectActorIdEnd    = kSceneObjectActorIdStart  +  73,
// 	kSceneObjectItemIdStart   = kSceneObjectActorIdEnd    +   1,
// 	kSceneObjectItemIdEnd     = kSceneObjectItemIdStart   + 123,
// 	kSceneObjectObjectIdStart = kSceneObjectItemIdEnd     +   1,
// 	kSceneObjectObjectIdEnd   = kSceneObjectObjectIdStart +  95
// };

enum SceneObjectOffset {
	kSceneObjectOffsetActors  = 0,
	kSceneObjectOffsetItems   = 74,
	kSceneObjectOffsetObjects = 198
};

enum ActorCombatStates {
	kActorCombatStateIdle = 0,
	kActorCombatStateCover = 1,
	kActorCombatStateApproachCloseAttack = 2,
	kActorCombatStateUncover = 3,
	kActorCombatStateAim = 4,
	kActorCombatStateRangedAttack = 5,
	kActorCombatStateCloseAttack = 6,
	kActorCombatStateFlee = 7,
	kActorCombatStateApproachRangedAttack = 8
};

enum PoliceMazeTrackInstruction {
	kPMTIActivate = -26,
	kPMTILeave = -25,
	kPMTIShoot = -24,
	kPMTIEnemyReset = -23,
	kPMTIEnemySet = -22,
	kPMTIFlagReset = -21,
	kPMTIFlagSet = -20,
	kPMTIVariableDec = -19,
	kPMTIVariableInc = -18,
	kPMTIVariableReset = -17,
	kPMTIVariableSet = -16,
	kPMTITargetSet = -15,
	kPMTIPausedReset1of3 = -14,
	kPMTIPausedReset1of2 = -13,
	kPMTIPausedSet = -12,
	kPMTIPausedReset = -11,
	kPMTIPlaySound = -10,
	kPMTIObstacleReset = -9,
	kPMTIObstacleSet = -8,
	kPMTIWaitRandom = -7,
	kPMTIRotate = -6,
	kPMTIFacing = -5,
	kPMTIRestart = -4,
	kPMTIWait = -3,
	kPMTIMove = -2,
	kPMTIPosition = -1,
	kPMTI26 = 0
};

enum PlayerAgenda {
	kPlayerAgendaPolite = 0,
	kPlayerAgendaNormal = 1,
	kPlayerAgendaSurly = 2,
	kPlayerAgendaErratic = 3,
	kPlayerAgendaUserChoice = 4
};

enum AffectionTowards {
	kAffectionTowardsNone = 0,
	kAffectionTowardsSteele = 1,
	kAffectionTowardsDektora = 2,
	kAffectionTowardsLucy = 3
};

enum GoalMcCoy {
	kGoalMcCoyDefault = 0,
	kGoalMcCoyDodge = 1
};

enum GoalSteele {
	kGoalSteeleDefault = 0,
	kGoalSteeleApprehendIzo = 100,
	kGoalSteeleGoToTB02 = 110,
	kGoalSteeleLeaveTB02 = 111,
	kGoalSteeleGoToPoliceStation = 112,
	kGoalSteeleWalkAround = 113,
	kGoalSteeleShootIzo = 120,
	kGoalSteeleArrestIzo = 121,
	kGoalSteeleIzoBlockedByMcCoy = 125,
	kGoalSteeleLeaveRC03 = 130,
	kGoalSteeleWalkAroundRestart = 190
};

enum GoalGuzza {
	kGoalGuzzaLeaveOffice = 100,
	kGoalGuzzaGoToHawkersCircle = 101,
	kGoalGuzzaGoToOffice = 102
};

enum GoalIzo {
	kGoalIzoDefault = 0,
	kGoalIzoPrepareCamera = 1,
	kGoalIzoTakePhoto = 2,
	kGoalIzoRunToUG02 = 3,
	kGoalIzoStopRunning = 100,
	kGoalIzoRunToRC03 = 101,
	kGoalIzoWaitingAtRC03 = 102,
	kGoalIzoEscape = 103, // how can this happen? can mccoy catch izo in ug02?
	kGoalIzoRC03Walk = 110,
	kGoalIzoRC03Run = 111,
	kGoalIzoRC03RunAway = 114,
	kGoalIzoGetArrested = 120,
	kGoalIzoGotArrested = 180,
	kGoalIzoGoToHC01 = 150,
	kGoalIzoGoToHC03 = 155,
	kGoalIzoDieHidden = 198,
	kGoalIzoDie = 199,

	kGoalIzoDead = 599
};

enum GoalTransient {
	kGoalTransientDefault = 0,
	kGoalTransientCT04Leave = 2
};

enum GoalBulletBob {
	kGoalBulletBobDefault = 0,
	kGoalBulletBobWarningMcCoy = 1,
	kGoalBulletBobShootMcCoy = 2,
	kGoalBulletBobShotMcCoy = 3, // has no use
	kGoalBulletBobDead = 4
};

enum GoalRunciter {
	kGoalRunciterDefault = 0,
	kGoalRunciterWalkAround = 1,
	kGoalRunciterHide = 2,
	kGoalRunciterAtShop = 300,
	kGoalRunciterDead = 599
};

enum GoalZuben {
	kGoalZubenDefault = 0,
	kGoalZubenCT01Leave = 1,
	kGoalZubenCT02Flee = 2,
	kGoalZubenCT07Spared = 4,
	kGoalZubenCT07Leave = 5,
	kGoalZubenDie = 6,
	kGoalZubenSpared = 7,
	kGoalZubenCT02PushPot = 8,
	kGoalZubenCT02RunToDoor = 9,
	kGoalZubenCT02OpenDoor = 10,
	kGoalZubenCT06JumpDown = 11,
	kGoalZubenCT06AttackMcCoy = 12,
	kGoalZubenCT06Hide = 13,
	kGoalZubenCT02PotDodgeCheck = 14,
	kGoalZubenFled = 20,
	kGoalZubenMA01AttackMcCoy = 21,
	kGoalZubenDead = 599
};

enum GoalOfficerLeary {
	kGoalOfficerLearyDefault = 0,
	kGoalOfficerLearyRC01WalkToCrowd = 1,
	kGoalOfficerLearyRC01CrowdInterrogation = 2
};

} // End of namespace BladeRunner

#endif
