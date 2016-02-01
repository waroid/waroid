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
{ EWEAPON::M134D_MINIGUN, EWEAPONKIND::GATLING, "22mm M134D Minigun", "gatling.wav" },
{ EWEAPON::STARSTREAK_AVENGER, EWEAPONKIND::ROCKET, "Starstreak Avenger", "rocket.wav" },
{ EWEAPON::GAU_19_B_HMG, EWEAPONKIND::GATLING, "12.7mm GAU-19/B HMG", "gatling.wav" },
{ EWEAPON::_2A72_AUTOCANNON, EWEAPONKIND::CANNON, "30mm 2A72 Autocannon", "cannon.wav" },
{ EWEAPON::XM214_MICROGUN, EWEAPONKIND::GATLING, "5.56mm XM214 Microgun", "gatling.wav" },
{ EWEAPON::M242_CHAINGUN, EWEAPONKIND::CANNON, "25mm M242 Chaingun", "cannon.wav" },
{ EWEAPON::BOFORS_L60, EWEAPONKIND::CANNON, "40mm Bofors L60", "cannon.wav" },
{ EWEAPON::M61_VULCAN, EWEAPONKIND::GATLING, "20mm M61 Vulcan", "gatling.wav" },
{ EWEAPON::PLASMA_GUN, EWEAPONKIND::CANNON, "Plasma Gun", "cannon.wav" },
{ EWEAPON::ENERGY_CANNON, EWEAPONKIND::CANNON, "Energy Cannon", "cannon.wav" },
{ EWEAPON::LASER_CANNON, EWEAPONKIND::CANNON, "Laser Cannon", "cannon.wav" } };

