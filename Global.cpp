/*
 * Global.cpp
 *
 *  Created on: Mar 3, 2015
 *      Author: mirime
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <syslog.h>

#include "Global.h"

const char* g_soundDir = "/usr/local/share/waroid";

const char* g_robotTypeNames[EROBOT::TOTAL] =
{ "TESTBOT", "CRABBOT", "HYDRABOT", "TAURUSBOT", "TURTLEBOT", "SCORPIOBOT", "TOADBOT", "WARTHOGBOT", "SPIDERBOT", "THORBOT", "HARPYBOT" };

WEAPON_DATA g_weaponDatas[EWEAPON::TOTAL] =
{
{ EWEAPON::NONE, EWEAPONKIND::NONE, "none", "" },
{ EWEAPON::M134D_MINIGUN, EWEAPONKIND::GATLING, "22mm M134D Minigun", "20mm_M134D_Minigun.wav" },
{ EWEAPON::STARSTREAK_AVENGER, EWEAPONKIND::ROCKET, "Starstreak Avenger", "Starstreak_Avenger.wav" },
{ EWEAPON::GAU_19_B_HMG, EWEAPONKIND::GATLING, "12.7mm GAU-19/B HMG", "12.7mm_GAU-19B_HMG.wav" },
{ EWEAPON::_2A72_AUTOCANNON, EWEAPONKIND::CANNON, "30mm 2A72 Autocannon", "30mm_2A72_Autocannon.wav" },
{ EWEAPON::XM214_MICROGUN, EWEAPONKIND::GATLING, "5.56mm XM214 Microgun", "5.56mm_XM214_Microgun.wav" },
{ EWEAPON::M242_CHAINGUN, EWEAPONKIND::CANNON, "25mm M242 Chaingun", "25mm_M242_Chaingun.wav" },
{ EWEAPON::BOFORS_L60, EWEAPONKIND::CANNON, "40mm Bofors L60", "40mm_Bofors_L60.wav" },
{ EWEAPON::M61_VULCAN, EWEAPONKIND::GATLING, "20mm M61 Vulcan", "20mm_M61_Vulcan.wav" },
{ EWEAPON::PLASMA_GUN, EWEAPONKIND::CANNON, "Plasma Gun", "plasma.wav" },
{ EWEAPON::ENERGY_CANNON, EWEAPONKIND::CANNON, "Energy Cannon", "energy.wav" },
{ EWEAPON::LASER_CANNON, EWEAPONKIND::CANNON, "Laser Cannon", "laser.wav" } };

