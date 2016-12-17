#pragma once
constexpr float tempo = 2.0;

//          BASIC
constexpr float BasicSize = 10.0;
constexpr float BasicRange = 70.0;
constexpr float BasicSpeed = 250.0;
constexpr float BasicAttackTimer = 1.0;
constexpr float BasicTimeSinceLastAttack = 0.0;

//          SNIPER
constexpr float SniperSize = BasicSize * 0.5;
constexpr float SniperRange = BasicRange * 3;
constexpr float SniperAttackTimer = BasicAttackTimer * 2;

//          TANK
constexpr float TankRange = 0.5;
constexpr float TankSpeed = 0.5;
constexpr float TankSize = BasicSize * 1.5;
constexpr float TankDmgReduce = 0.7;

//          THE GAME
constexpr float ScreenWidth = 1920.0;
constexpr float ScreenHeigth = 1080.0;

//   PRESENTATON VARIABLES
constexpr int SniperCd1 = 4;
constexpr int TankCd1 = 20;

constexpr int SniperCd2 = 10;
constexpr int TankCd2 = 10;

constexpr int SniperCd3 = 3;
constexpr int TankCd3 = 2;

constexpr int SniperCd4 = 7;
constexpr int TankCd4 = 30;