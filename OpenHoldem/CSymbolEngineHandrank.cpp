//******************************************************************************
//
// This file is part of the OpenHoldem project
//   Download page:         http://code.google.com/p/openholdembot/
//   Forums:                http://www.maxinmontreal.com/forums/index.php
//   Licensed under GPL v3: http://www.gnu.org/licenses/gpl.html
//
//******************************************************************************
//
// Purpose:
//
//******************************************************************************

#include "stdafx.h"
#include "CSymbolEngineHandrank.h"

#include <assert.h>
#include "CScraper.h"
#include "CSymbolEnginePrwin.h"
#include "CSymbolEngineUserchair.h"
#include "MagicNumbers.h"

CSymbolEngineHandrank *p_symbol_engine_handrank = NULL;

int handrank_table_2652[k_max_number_of_players][k_number_of_starting_hands] =
{
	{12, 24, 36, 48, 60, 72, 84, 92, 104, 112, 136, 144, 168, 176, 188, 212, 220, 244, 252, 260, 268, 276, 300, 312, 320, 344, 368, 376, 384, 408, 432, 440, 448, 456, 464, 488, 512, 520, 528, 552, 564, 572, 580, 604, 628, 636, 660, 668, 676, 700, 724, 732, 740, 764, 772, 796, 820, 844, 868, 876, 888, 896, 920, 928, 936, 944, 968, 976, 1000, 1024, 1032, 1040, 1048, 1056, 1080, 1104, 1128, 1136, 1160, 1184, 1196, 1220, 1228, 1236, 1244, 1252, 1276, 1284, 1308, 1316, 1340, 1364, 1388, 1396, 1404, 1412, 1420, 1444, 1468, 1492, 1516, 1524, 1532, 1540, 1564, 1588, 1596, 1604, 1628, 1652, 1676, 1684, 1692, 1700, 1724, 1732, 1756, 1764, 1788, 1812, 1820, 1844, 1852, 1876, 1884, 1892, 1916, 1924, 1948, 1972, 1980, 1988, 2012, 2036, 2044, 2068, 2076, 2084, 2092, 2116, 2140, 2148, 2172, 2180, 2204, 2212, 2220, 2244, 2268, 2276, 2300, 2308, 2332, 2356, 2364, 2372, 2396, 2420, 2428, 2452, 2476, 2500, 2508, 2532, 2556, 2580, 2604, 2628, 2652},
	{12, 24, 36, 48, 60, 72, 80, 92, 100, 124, 132, 144, 152, 160, 184, 192, 216, 224, 248, 256, 264, 288, 300, 308, 332, 340, 348, 356, 364, 388, 412, 436, 448, 456, 464, 472, 496, 520, 528, 536, 544, 568, 576, 600, 608, 632, 640, 648, 656, 664, 676, 700, 724, 748, 756, 764, 788, 796, 820, 844, 852, 860, 868, 892, 916, 940, 948, 956, 964, 988, 1012, 1024, 1048, 1056, 1064, 1072, 1096, 1104, 1112, 1120, 1144, 1168, 1176, 1184, 1208, 1232, 1256, 1264, 1272, 1280, 1288, 1312, 1320, 1328, 1352, 1364, 1388, 1396, 1420, 1444, 1452, 1476, 1484, 1508, 1532, 1540, 1548, 1556, 1564, 1588, 1596, 1604, 1628, 1636, 1660, 1668, 1692, 1716, 1724, 1748, 1756, 1780, 1804, 1828, 1836, 1844, 1852, 1876, 1884, 1892, 1916, 1924, 1948, 1956, 1980, 1988, 1996, 2020, 2044, 2052, 2076, 2100, 2124, 2132, 2140, 2164, 2188, 2196, 2204, 2228, 2236, 2260, 2284, 2308, 2332, 2340, 2364, 2388, 2412, 2436, 2460, 2484, 2508, 2532, 2556, 2580, 2604, 2628, 2652},
	{12, 24, 36, 48, 60, 72, 80, 88, 112, 120, 128, 140, 148, 172, 180, 188, 196, 220, 244, 256, 264, 272, 296, 304, 328, 336, 344, 368, 380, 404, 412, 420, 444, 452, 460, 468, 492, 500, 524, 532, 540, 552, 560, 568, 576, 600, 624, 632, 640, 648, 656, 664, 688, 712, 720, 744, 768, 776, 800, 812, 820, 844, 868, 876, 884, 892, 900, 908, 916, 940, 948, 956, 980, 1004, 1028, 1052, 1060, 1084, 1092, 1100, 1124, 1148, 1160, 1184, 1192, 1200, 1208, 1216, 1224, 1232, 1256, 1264, 1272, 1296, 1304, 1328, 1336, 1344, 1368, 1392, 1400, 1408, 1432, 1456, 1468, 1492, 1500, 1508, 1516, 1540, 1548, 1572, 1580, 1604, 1612, 1620, 1628, 1652, 1676, 1684, 1692, 1716, 1740, 1764, 1788, 1796, 1820, 1828, 1836, 1860, 1868, 1876, 1900, 1924, 1932, 1956, 1964, 1988, 1996, 2020, 2028, 2052, 2076, 2084, 2108, 2132, 2140, 2164, 2188, 2196, 2220, 2244, 2268, 2292, 2316, 2340, 2364, 2388, 2412, 2436, 2460, 2484, 2508, 2532, 2556, 2580, 2604, 2628, 2652},
	{12, 24, 36, 48, 60, 68, 76, 88, 96, 120, 128, 136, 144, 168, 180, 188, 196, 220, 228, 252, 260, 268, 292, 304, 328, 336, 344, 368, 376, 400, 408, 416, 424, 448, 456, 468, 492, 500, 508, 516, 540, 548, 556, 564, 572, 580, 588, 596, 620, 632, 640, 664, 688, 696, 720, 728, 752, 760, 768, 776, 784, 808, 816, 824, 832, 844, 868, 892, 900, 908, 932, 940, 964, 972, 980, 1004, 1012, 1036, 1044, 1052, 1076, 1100, 1124, 1132, 1156, 1168, 1176, 1184, 1192, 1216, 1224, 1232, 1256, 1264, 1272, 1280, 1292, 1300, 1308, 1316, 1324, 1348, 1372, 1396, 1404, 1428, 1452, 1476, 1484, 1508, 1516, 1524, 1548, 1556, 1564, 1588, 1596, 1604, 1612, 1636, 1660, 1668, 1692, 1716, 1724, 1732, 1756, 1764, 1788, 1812, 1836, 1844, 1852, 1876, 1884, 1908, 1932, 1940, 1964, 1972, 1996, 2004, 2028, 2052, 2076, 2100, 2124, 2148, 2172, 2196, 2220, 2244, 2268, 2292, 2316, 2340, 2364, 2388, 2412, 2436, 2460, 2484, 2508, 2532, 2556, 2580, 2604, 2628, 2652},
	{12, 24, 36, 48, 56, 68, 76, 84, 108, 116, 128, 136, 144, 152, 176, 184, 208, 216, 228, 236, 260, 268, 292, 300, 308, 332, 356, 368, 376, 384, 392, 416, 424, 432, 456, 480, 488, 496, 504, 516, 524, 532, 540, 548, 556, 564, 572, 596, 604, 628, 640, 648, 656, 664, 688, 712, 720, 728, 736, 760, 768, 792, 800, 808, 820, 828, 836, 844, 868, 876, 900, 908, 916, 924, 936, 960, 968, 976, 984, 1008, 1032, 1056, 1064, 1088, 1096, 1104, 1128, 1152, 1160, 1172, 1196, 1220, 1228, 1236, 1244, 1252, 1260, 1284, 1292, 1300, 1324, 1332, 1340, 1348, 1372, 1380, 1404, 1412, 1436, 1444, 1452, 1476, 1500, 1508, 1532, 1540, 1564, 1572, 1580, 1588, 1612, 1636, 1644, 1668, 1676, 1700, 1708, 1732, 1756, 1764, 1772, 1780, 1804, 1828, 1852, 1876, 1900, 1908, 1932, 1956, 1980, 2004, 2028, 2052, 2076, 2100, 2124, 2148, 2172, 2196, 2220, 2244, 2268, 2292, 2316, 2340, 2364, 2388, 2412, 2436, 2460, 2484, 2508, 2532, 2556, 2580, 2604, 2628, 2652},
	{12, 24, 36, 48, 56, 64, 76, 84, 92, 116, 124, 132, 140, 152, 160, 184, 192, 200, 224, 236, 244, 268, 276, 300, 308, 316, 340, 348, 356, 380, 392, 400, 424, 432, 440, 464, 472, 480, 504, 512, 524, 532, 540, 548, 556, 564, 572, 580, 592, 616, 624, 632, 640, 648, 656, 664, 688, 696, 704, 728, 740, 748, 772, 796, 804, 812, 836, 844, 852, 864, 872, 880, 888, 900, 908, 916, 940, 948, 956, 964, 972, 996, 1004, 1028, 1036, 1044, 1068, 1092, 1100, 1124, 1148, 1172, 1196, 1204, 1212, 1236, 1244, 1252, 1260, 1268, 1292, 1300, 1308, 1332, 1340, 1348, 1356, 1364, 1388, 1412, 1420, 1428, 1452, 1460, 1468, 1476, 1500, 1524, 1532, 1556, 1580, 1588, 1612, 1620, 1628, 1652, 1660, 1684, 1708, 1732, 1740, 1764, 1788, 1812, 1836, 1860, 1884, 1908, 1932, 1956, 1980, 2004, 2028, 2052, 2076, 2100, 2124, 2148, 2172, 2196, 2220, 2244, 2268, 2292, 2316, 2340, 2364, 2388, 2412, 2436, 2460, 2484, 2508, 2532, 2556, 2580, 2604, 2628, 2652},
	{12, 24, 36, 48, 56, 64, 72, 84, 92, 116, 124, 132, 140, 148, 160, 168, 192, 200, 224, 232, 244, 268, 276, 284, 292, 316, 324, 332, 356, 368, 376, 384, 408, 416, 440, 448, 456, 464, 488, 512, 524, 532, 540, 548, 556, 564, 572, 580, 592, 600, 608, 616, 628, 636, 644, 652, 660, 668, 692, 700, 712, 720, 728, 740, 764, 772, 796, 804, 812, 836, 860, 868, 876, 884, 908, 916, 924, 932, 940, 948, 956, 964, 972, 980, 1004, 1012, 1036, 1044, 1052, 1060, 1084, 1092, 1100, 1124, 1148, 1156, 1180, 1204, 1212, 1220, 1244, 1268, 1292, 1300, 1308, 1316, 1324, 1348, 1372, 1380, 1404, 1412, 1420, 1428, 1436, 1444, 1468, 1492, 1500, 1508, 1532, 1540, 1564, 1588, 1612, 1620, 1644, 1668, 1692, 1716, 1740, 1764, 1788, 1812, 1836, 1860, 1884, 1908, 1932, 1956, 1980, 2004, 2028, 2052, 2076, 2100, 2124, 2148, 2172, 2196, 2220, 2244, 2268, 2292, 2316, 2340, 2364, 2388, 2412, 2436, 2460, 2484, 2508, 2532, 2556, 2580, 2604, 2628, 2652},
	{12, 24, 36, 44, 56, 64, 72, 80, 92, 116, 124, 132, 140, 148, 156, 168, 176, 200, 224, 232, 244, 252, 260, 284, 292, 300, 308, 332, 344, 352, 360, 384, 392, 400, 408, 432, 440, 452, 460, 468, 492, 500, 508, 516, 540, 564, 572, 584, 592, 600, 612, 620, 632, 644, 652, 660, 668, 676, 684, 692, 700, 708, 716, 724, 732, 740, 764, 772, 796, 804, 812, 820, 844, 868, 876, 884, 892, 916, 924, 932, 940, 948, 972, 980, 988, 996, 1004, 1012, 1020, 1028, 1036, 1044, 1068, 1092, 1116, 1124, 1148, 1156, 1164, 1172, 1196, 1204, 1212, 1236, 1260, 1284, 1308, 1316, 1340, 1348, 1356, 1364, 1388, 1412, 1420, 1428, 1452, 1460, 1484, 1492, 1516, 1524, 1548, 1572, 1596, 1620, 1644, 1668, 1692, 1716, 1740, 1764, 1788, 1812, 1836, 1860, 1884, 1908, 1932, 1956, 1980, 2004, 2028, 2052, 2076, 2100, 2124, 2148, 2172, 2196, 2220, 2244, 2268, 2292, 2316, 2340, 2364, 2388, 2412, 2436, 2460, 2484, 2508, 2532, 2556, 2580, 2604, 2628, 2652},
	{12, 24, 36, 44, 56, 64, 72, 80, 92, 100, 124, 132, 140, 148, 156, 164, 176, 200, 208, 232, 244, 252, 260, 268, 276, 284, 296, 320, 328, 336, 344, 368, 376, 388, 396, 420, 428, 436, 444, 452, 460, 484, 492, 504, 512, 536, 560, 572, 584, 596, 620, 628, 636, 644, 652, 660, 668, 676, 684, 692, 700, 708, 716, 724, 732, 740, 748, 756, 764, 772, 780, 788, 812, 820, 844, 852, 860, 868, 876, 900, 924, 932, 940, 964, 972, 980, 988, 996, 1004, 1012, 1036, 1044, 1052, 1060, 1068, 1076, 1084, 1108, 1116, 1140, 1164, 1188, 1196, 1204, 1228, 1236, 1244, 1252, 1276, 1300, 1324, 1332, 1356, 1380, 1404, 1412, 1436, 1444, 1468, 1476, 1500, 1524, 1548, 1572, 1596, 1620, 1644, 1668, 1692, 1716, 1740, 1764, 1788, 1812, 1836, 1860, 1884, 1908, 1932, 1956, 1980, 2004, 2028, 2052, 2076, 2100, 2124, 2148, 2172, 2196, 2220, 2244, 2268, 2292, 2316, 2340, 2364, 2388, 2412, 2436, 2460, 2484, 2508, 2532, 2556, 2580, 2604, 2628, 2652}
};

const int k_max_length_of_entry_including_zero_char = 4;
char handrank_table_169[k_max_number_of_players][k_number_of_starting_hands][k_max_length_of_entry_including_zero_char] = {
  {"AAo", "KKo", "QQo", "JJo", "TTo", "99o", "88o", "AKs", "77o", "AQs", "AKo", "AJs", "AQo", "ATs", "66o", "AJo", "KQs", "ATo", "A9s", "KJs", "A8s", "KTs", "KQo", "55o", "A7s", "A9o", "KJo", "QJs", "K9s", "KTo", "A8o", "A6s", "QTs", "A5s", "A4s", "A7o", "QJo", "K8s", "A3s", "K9o", "44o", "Q9s", "JTs", "QTo", "A6o", "K7s", "A5o", "A2s", "K6s", "A4o", "K8o", "Q8s", "J9s", "A3o", "K5s", "Q9o", "JTo", "K7o", "A2o", "K4s", "33o", "Q7s", "K6o", "T9s", "J8s", "K3s", "Q8o", "Q6s", "J9o", "K5o", "K2s", "Q5s", "T8s", "J7s", "K4o", "Q7o", "T9o", "Q4s", "J8o", "K3o", "22o", "Q6o", "Q3s", "98s", "T7s", "J6s", "K2o", "Q2s", "Q5o", "J5s", "T8o", "J7o", "Q4o", "97s", "J4s", "T6s", "J3s", "Q3o", "98o", "T7o", "J6o", "87s", "J2s", "96s", "Q2o", "J5o", "T5s", "T4s", "97o", "J4o", "T6o", "86s", "95s", "T3s", "J3o", "76s", "87o", "T2s", "96o", "J2o", "85s", "T5o", "94s", "T4o", "75s", "93s", "86o", "65s", "95o", "T3o", "84s", "92s", "76o", "T2o", "74s", "85o", "54s", "64s", "83s", "94o", "75o", "82s", "93o", "73s", "65o", "53s", "63s", "84o", "92o", "43s", "74o", "72s", "54o", "64o", "52s", "62s", "83o", "82o", "42s", "73o", "53o", "63o", "32s", "43o", "72o", "52o", "62o", "42o", "32o"},
  {"AAo", "KKo", "QQo", "JJo", "TTo", "99o", "AKs", "88o", "AQs", "AKo", "AJs", "77o", "KQs", "ATs", "AQo", "KJs", "AJo", "KTs", "KQo", "A9s", "QJs", "ATo", "66o", "A8s", "KJo", "QTs", "K9s", "JTs", "A7s", "KTo", "QJo", "A9o", "55o", "A5s", "A6s", "Q9s", "QTo", "A8o", "K8s", "A4s", "J9s", "K9o", "A3s", "JTo", "K7s", "A7o", "T9s", "Q8s", "A2s", "K6s", "44o", "Q9o", "A5o", "A6o", "J8s", "K5s", "K8o", "T8s", "A4o", "J9o", "Q7s", "K4s", "98s", "A3o", "K7o", "T9o", "Q6s", "K3s", "J7s", "Q8o", "A2o", "33o", "K6o", "Q5s", "K2s", "T7s", "J8o", "97s", "87s", "Q4s", "K5o", "T8o", "J6s", "Q3s", "Q7o", "98o", "K4o", "T6s", "J5s", "Q2s", "96s", "Q6o", "76s", "86s", "J7o", "22o", "K3o", "J4s", "T7o", "Q5o", "J3s", "K2o", "T5s", "97o", "87o", "65s", "J2s", "95s", "75s", "Q4o", "T4s", "85s", "J6o", "T3s", "Q3o", "54s", "T6o", "J5o", "T2s", "96o", "64s", "86o", "76o", "Q2o", "94s", "74s", "84s", "J4o", "93s", "53s", "J3o", "92s", "T5o", "63s", "65o", "73s", "43s", "95o", "75o", "83s", "J2o", "85o", "T4o", "82s", "52s", "T3o", "54o", "62s", "42s", "64o", "72s", "T2o", "74o", "94o", "84o", "32s", "93o", "53o", "92o", "63o", "43o", "73o", "83o", "82o", "52o", "62o", "42o", "72o", "32o"},
  {"AAo", "KKo", "QQo", "JJo", "TTo", "99o", "AKs", "AQs", "AKo", "AJs", "KQs", "88o", "ATs", "AQo", "KJs", "QJs", "KTs", "KQo", "AJo", "77o", "QTs", "A9s", "ATo", "JTs", "KJo", "A8s", "K9s", "QJo", "66o", "KTo", "A7s", "Q9s", "QTo", "J9s", "A5s", "T9s", "A9o", "A6s", "JTo", "K8s", "A4s", "55o", "A3s", "K7s", "Q8s", "A8o", "K9o", "J8s", "A2s", "T8s", "K6s", "98s", "Q9o", "A7o", "K5s", "J9o", "T9o", "Q7s", "A5o", "44o", "K4s", "A6o", "K8o", "J7s", "Q6s", "T7s", "97s", "87s", "K3s", "A4o", "Q5s", "K2s", "Q8o", "K7o", "A3o", "J8o", "Q4s", "T8o", "J6s", "76s", "A2o", "98o", "33o", "K6o", "T6s", "86s", "96s", "Q3s", "J5s", "Q2s", "K5o", "J4s", "65s", "Q7o", "75s", "J7o", "J3s", "85s", "K4o", "T7o", "T5s", "95s", "97o", "87o", "22o", "Q6o", "J2s", "54s", "T4s", "K3o", "64s", "Q5o", "T3s", "K2o", "74s", "84s", "T2s", "76o", "Q4o", "94s", "53s", "J6o", "T6o", "86o", "96o", "93s", "Q3o", "63s", "43s", "J5o", "92s", "73s", "Q2o", "65o", "83s", "J4o", "52s", "75o", "82s", "85o", "42s", "J3o", "T5o", "62s", "95o", "54o", "72s", "T4o", "J2o", "32s", "64o", "T3o", "74o", "84o", "T2o", "53o", "94o", "93o", "63o", "43o", "92o", "73o", "83o", "52o", "82o", "42o", "62o", "72o", "32o"},
  {"AAo", "KKo", "QQo", "JJo", "TTo", "AKs", "AQs", "99o", "KQs", "AKo", "AJs", "KJs", "ATs", "AQo", "88o", "QJs", "KTs", "KQo", "QTs", "AJo", "JTs", "A9s", "KJo", "77o", "ATo", "K9s", "A8s", "QJo", "Q9s", "KTo", "A7s", "J9s", "T9s", "QTo", "A5s", "66o", "JTo", "A6s", "K8s", "A4s", "A9o", "A3s", "Q8s", "K7s", "J8s", "T8s", "A2s", "98s", "K9o", "55o", "K6s", "A8o", "Q9o", "K5s", "T9o", "Q7s", "J9o", "K4s", "T7s", "J7s", "87s", "A7o", "97s", "Q6s", "K3s", "44o", "A5o", "K8o", "K2s", "Q5s", "A6o", "76s", "A4o", "86s", "Q4s", "Q8o", "J6s", "T8o", "T6s", "96s", "J8o", "A3o", "K7o", "Q3s", "98o", "33o", "J5s", "65s", "Q2s", "A2o", "75s", "J4s", "K6o", "85s", "54s", "J3s", "22o", "T5s", "95s", "J2s", "64s", "K5o", "Q7o", "87o", "T4s", "T7o", "J7o", "97o", "74s", "K4o", "T3s", "53s", "Q6o", "84s", "T2s", "K3o", "94s", "43s", "63s", "76o", "Q5o", "93s", "K2o", "86o", "92s", "73s", "96o", "52s", "Q4o", "J6o", "T6o", "83s", "42s", "65o", "82s", "Q3o", "J5o", "62s", "75o", "32s", "Q2o", "72s", "J4o", "54o", "85o", "95o", "T5o", "J3o", "64o", "J2o", "T4o", "74o", "53o", "T3o", "84o", "T2o", "94o", "43o", "63o", "93o", "73o", "92o", "52o", "83o", "42o", "82o", "62o", "32o", "72o"},
  {"AAo", "KKo", "QQo", "JJo", "AKs", "TTo", "AQs", "KQs", "AKo", "AJs", "99o", "KJs", "ATs", "QJs", "AQo", "KTs", "KQo", "QTs", "88o", "JTs", "AJo", "A9s", "KJo", "K9s", "A8s", "QJo", "ATo", "77o", "Q9s", "T9s", "J9s", "KTo", "A7s", "A5s", "QTo", "JTo", "K8s", "A4s", "A6s", "66o", "A3s", "Q8s", "T8s", "K7s", "J8s", "98s", "A2s", "A9o", "K6s", "K9o", "55o", "K5s", "87s", "Q7s", "A8o", "Q9o", "T7s", "97s", "K4s", "T9o", "J7s", "J9o", "K3s", "Q6s", "44o", "K2s", "76s", "Q5s", "A7o", "86s", "A5o", "Q4s", "96s", "T6s", "33o", "K8o", "J6s", "65s", "Q3s", "A6o", "A4o", "T8o", "J5s", "Q8o", "Q2s", "75s", "J8o", "98o", "54s", "22o", "A3o", "K7o", "J4s", "85s", "J3s", "64s", "95s", "A2o", "T5s", "J2s", "K6o", "T4s", "53s", "74s", "87o", "T3s", "97o", "43s", "T7o", "T2s", "84s", "K5o", "Q7o", "63s", "J7o", "94s", "K4o", "93s", "52s", "73s", "Q6o", "76o", "92s", "K3o", "42s", "86o", "83s", "K2o", "Q5o", "82s", "62s", "32s", "96o", "65o", "T6o", "Q4o", "J6o", "72s", "75o", "Q3o", "54o", "J5o", "Q2o", "85o", "J4o", "64o", "95o", "J3o", "T5o", "53o", "J2o", "74o", "T4o", "43o", "T3o", "84o", "63o", "T2o", "94o", "52o", "93o", "73o", "42o", "92o", "83o", "62o", "32o", "82o", "72o"},
  {"AAo", "KKo", "QQo", "JJo", "AKs", "AQs", "TTo", "KQs", "AJs", "AKo", "KJs", "ATs", "QJs", "99o", "KTs", "AQo", "QTs", "JTs", "KQo", "88o", "A9s", "AJo", "K9s", "KJo", "A8s", "Q9s", "QJo", "T9s", "J9s", "ATo", "77o", "A7s", "KTo", "A5s", "A4s", "QTo", "K8s", "A6s", "JTo", "A3s", "66o", "T8s", "Q8s", "A2s", "J8s", "K7s", "98s", "K6s", "55o", "A9o", "87s", "K5s", "97s", "Q7s", "K4s", "T7s", "K9o", "J7s", "K3s", "T9o", "44o", "Q6s", "Q9o", "J9o", "K2s", "76s", "A8o", "86s", "Q5s", "33o", "65s", "Q4s", "96s", "22o", "T6s", "Q3s", "A7o", "J6s", "75s", "54s", "Q2s", "A5o", "J5s", "K8o", "85s", "64s", "A4o", "T8o", "J4s", "A6o", "98o", "Q8o", "J8o", "J3s", "53s", "A3o", "95s", "J2s", "T5s", "74s", "K7o", "T4s", "43s", "A2o", "T3s", "84s", "63s", "T2s", "87o", "K6o", "52s", "94s", "97o", "93s", "73s", "42s", "T7o", "K5o", "92s", "Q7o", "J7o", "32s", "76o", "83s", "62s", "K4o", "82s", "86o", "Q6o", "K3o", "72s", "K2o", "65o", "96o", "Q5o", "54o", "T6o", "75o", "Q4o", "J6o", "Q3o", "Q2o", "85o", "64o", "J5o", "53o", "J4o", "95o", "J3o", "74o", "T5o", "43o", "J2o", "T4o", "63o", "T3o", "84o", "52o", "T2o", "94o", "42o", "73o", "93o", "92o", "32o", "83o", "62o", "82o", "72o"},
  {"AAo", "KKo", "QQo", "JJo", "AKs", "AQs", "KQs", "TTo", "AJs", "AKo", "KJs", "ATs", "QJs", "KTs", "99o", "QTs", "AQo", "JTs", "KQo", "A9s", "88o", "AJo", "K9s", "A8s", "T9s", "KJo", "Q9s", "J9s", "QJo", "77o", "A7s", "A5s", "ATo", "A4s", "KTo", "A6s", "K8s", "A3s", "JTo", "QTo", "66o", "T8s", "A2s", "Q8s", "98s", "J8s", "K7s", "K6s", "55o", "87s", "K5s", "97s", "44o", "K4s", "T7s", "Q7s", "J7s", "K3s", "A9o", "76s", "33o", "K2s", "Q6s", "22o", "K9o", "86s", "T9o", "65s", "Q5s", "J9o", "Q9o", "96s", "54s", "Q4s", "A8o", "75s", "T6s", "Q3s", "J6s", "Q2s", "64s", "85s", "J5s", "53s", "A7o", "J4s", "A5o", "J3s", "95s", "74s", "T8o", "J2s", "43s", "A4o", "K8o", "T5s", "98o", "J8o", "T4s", "63s", "A6o", "A3o", "Q8o", "T3s", "84s", "T2s", "52s", "A2o", "K7o", "42s", "87o", "94s", "73s", "93s", "92s", "32s", "97o", "K6o", "62s", "83s", "T7o", "82s", "76o", "K5o", "J7o", "72s", "Q7o", "K4o", "86o", "65o", "K3o", "Q6o", "K2o", "54o", "96o", "75o", "Q5o", "T6o", "Q4o", "64o", "J6o", "Q3o", "85o", "53o", "Q2o", "J5o", "74o", "43o", "J4o", "95o", "J3o", "J2o", "63o", "T5o", "52o", "T4o", "84o", "T3o", "42o", "T2o", "73o", "94o", "32o", "93o", "62o", "92o", "83o", "82o", "72o"},
  {"AAo", "KKo", "QQo", "AKs", "JJo", "AQs", "KQs", "AJs", "TTo", "AKo", "KJs", "ATs", "QJs", "KTs", "QTs", "99o", "JTs", "AQo", "KQo", "A9s", "88o", "K9s", "T9s", "AJo", "A8s", "J9s", "Q9s", "KJo", "77o", "A5s", "A7s", "QJo", "A4s", "A3s", "A6s", "ATo", "K8s", "66o", "A2s", "T8s", "KTo", "98s", "Q8s", "J8s", "JTo", "QTo", "K7s", "55o", "87s", "K6s", "44o", "97s", "33o", "22o", "K5s", "T7s", "K4s", "76s", "Q7s", "K3s", "J7s", "K2s", "86s", "65s", "Q6s", "54s", "A9o", "Q5s", "T9o", "96s", "75s", "Q4s", "K9o", "J9o", "Q3s", "64s", "T6s", "Q9o", "Q2s", "J6s", "85s", "53s", "A8o", "J5s", "J4s", "74s", "43s", "J3s", "95s", "J2s", "63s", "T5s", "A5o", "A7o", "T8o", "T4s", "98o", "T3s", "84s", "52s", "A4o", "T2s", "42s", "K8o", "A3o", "J8o", "A6o", "73s", "Q8o", "94s", "32s", "93s", "A2o", "87o", "92s", "62s", "K7o", "83s", "97o", "82s", "76o", "72s", "K6o", "T7o", "65o", "K5o", "86o", "J7o", "54o", "Q7o", "K4o", "K3o", "75o", "K2o", "Q6o", "96o", "64o", "Q5o", "T6o", "53o", "Q4o", "85o", "J6o", "Q3o", "Q2o", "43o", "74o", "J5o", "J4o", "95o", "63o", "J3o", "J2o", "52o", "T5o", "84o", "42o", "T4o", "T3o", "32o", "T2o", "73o", "94o", "62o", "93o", "92o", "83o", "82o", "72o"},
  {"AAo", "KKo", "QQo", "AKs", "JJo", "AQs", "KQs", "AJs", "TTo", "KJs", "AKo", "ATs", "QJs", "KTs", "QTs", "JTs", "99o", "AQo", "A9s", "KQo", "88o", "K9s", "T9s", "A8s", "J9s", "Q9s", "77o", "AJo", "A5s", "A7s", "A4s", "KJo", "A3s", "66o", "A6s", "QJo", "K8s", "A2s", "T8s", "98s", "J8s", "ATo", "Q8s", "55o", "K7s", "JTo", "KTo", "44o", "33o", "22o", "QTo", "87s", "K6s", "97s", "K5s", "76s", "T7s", "K4s", "K3s", "Q7s", "K2s", "J7s", "86s", "65s", "54s", "Q6s", "75s", "Q5s", "96s", "Q4s", "Q3s", "64s", "T9o", "Q2s", "A9o", "T6s", "53s", "J6s", "85s", "J9o", "K9o", "43s", "J5s", "Q9o", "74s", "J4s", "J3s", "J2s", "95s", "63s", "A8o", "T5s", "52s", "42s", "T4s", "T3s", "84s", "98o", "T2s", "A5o", "T8o", "A7o", "73s", "32s", "A4o", "94s", "93s", "62s", "A3o", "K8o", "J8o", "92s", "A6o", "87o", "Q8o", "83s", "A2o", "82s", "97o", "72s", "K7o", "76o", "T7o", "65o", "K6o", "86o", "54o", "K5o", "J7o", "Q7o", "75o", "K4o", "K3o", "96o", "64o", "K2o", "53o", "Q6o", "85o", "T6o", "Q5o", "43o", "Q4o", "Q3o", "74o", "Q2o", "J6o", "63o", "J5o", "95o", "52o", "J4o", "42o", "J3o", "J2o", "84o", "T5o", "32o", "T4o", "T3o", "73o", "T2o", "62o", "94o", "93o", "92o", "83o", "82o", "72o"}
};

CSymbolEngineHandrank::CSymbolEngineHandrank()
{
	// The values of some symbol-engines depend on other engines.
	// As the engines get later called in the order of initialization
	// we assure correct ordering by checking if they are initialized.
	assert(p_symbol_engine_prwin != NULL);
	assert(p_symbol_engine_userchair != NULL);
}

CSymbolEngineHandrank::~CSymbolEngineHandrank()
{}

void CSymbolEngineHandrank::InitOnStartup()
{
	ResetOnHandreset();
}

void CSymbolEngineHandrank::ResetOnConnection()
{}

void CSymbolEngineHandrank::ResetOnHandreset()
{
	_handrank169  = 0;
	_handrank2652 = 0;
	_handrank1326 = 0;
	_handrank1000 = 0;
	_handrankp    = 0;
}

void CSymbolEngineHandrank::ResetOnNewRound()
{}

void CSymbolEngineHandrank::ResetOnMyTurn()
{
	__TRACE
	char		cardstr[10] = {0};

	// Get name string containing the players' current cards
	GetCardstring(cardstr, 
		p_scraper->card_player(USER_CHAIR, 0), 
		p_scraper->card_player(USER_CHAIR, 1));

	// if nopponents<1 or >9 then default to name sane value
	int _nopponents = p_symbol_engine_prwin->nopponents_for_prwin();
		
	for (int i=0; i<k_number_of_starting_hands; i++)
	{
		if (strcmp(cardstr, handrank_table_169[_nopponents-1][i])==0)
		{
			_handrank169  = i + 1;													
			_handrank2652 = handrank_table_2652[_nopponents-1][i];								
			break;
		}
	}

	_handrank1326 = _handrank2652 / 2;											
	_handrank1000 = 1000 * _handrank2652 / 2652;									
	_handrankp    = 2652.0 / (1.0 + (double)_nopponents);	
}

void CSymbolEngineHandrank::ResetOnHeartbeat()
{}

void CSymbolEngineHandrank::GetCardstring(char *c, unsigned int c0, unsigned int c1)
{
	char		card0[10] = {0}, card1[10] = {0};

	// figure out the card string to search for
	if (StdDeck_RANK(c0) >= StdDeck_RANK(c1))
	{
		StdDeck_cardToString(c0, card0);
		StdDeck_cardToString(c1, card1);
	}
	else
	{
		StdDeck_cardToString(c1, card0);
		StdDeck_cardToString(c0, card1);
	}
	c[0] = card0[0];
	c[1] = card1[0];

	if (c[0] == c[1] || card0[1] != card1[1])
	{
		c[2] = 'o';
	}
	else 
	{
		c[2] = 's';
	}
	c[3]='\0';
}

bool CSymbolEngineHandrank::EvaluateSymbol(const char *name, double *result, bool log /* = false */)
{
	if (memcmp(name, "handrank", 8) == 0)
	{
		if (memcmp(name, "handrank169", 11)==0 && strlen(name)==11)
		{
			*result = handrank169();
		}
		else if (memcmp(name, "handrank2652", 12)==0 && strlen(name)==12)
		{
			*result = handrank2652();
		}
		else if (memcmp(name, "handrank1326", 12)==0 && strlen(name)==12)
		{
			*result = handrank1326();
		}
		else if (memcmp(name, "handrank1000", 12)==0 && strlen(name)==12)
		{
			*result = handrank1000();
		}
		else if (memcmp(name, "handrankp", 9)==0 && strlen(name)==9)
		{
			*result = handrankp();
		}
		else
		{
			// Invalid symbol
			return false;
		}
		// Valid symbol
		return true;
	}
	// Symbol of a different symbol-engine
	return false;
}

CString CSymbolEngineHandrank::SymbolsProvided() {
  return "handrank169 handrank2652 handrank1326 handrank1000 handrankp ";
}