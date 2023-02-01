/*
 * inferenceset.c
 *
 *  Created on: Jan 26, 2023
 *      Author: mateo
 */

#include "inferenceset.h"

#ifndef DEBUG
#pragma PERSISTENT(X_inference)
#endif
fixed X_inference[N_INFERENCE][N_FEATURE] = {{ F_LIT(122.0), F_LIT(31.0), F_LIT(27.6), F_LIT(45.0) },    // 0
                                { F_LIT(105.0), F_LIT(21.0), F_LIT(30.05), F_LIT(24.0) },   // 0
                                { F_LIT(163.0), F_LIT(41.0), F_LIT(40.9), F_LIT(47.0) },    // 1
                                { F_LIT(110.0), F_LIT(21.0), F_LIT(37.6), F_LIT(30.0) },    // 0
                                { F_LIT(118.0), F_LIT(19.0), F_LIT(23.1), F_LIT(46.0) },    // 0
                                { F_LIT(99.0), F_LIT(10.0), F_LIT(25.4), F_LIT(21.0) },     // 0
                                { F_LIT(158.0), F_LIT(36.0), F_LIT(31.6), F_LIT(28.0) },    // 1
                                { F_LIT(171.0), F_LIT(27.0), F_LIT(43.6), F_LIT(26.0) },    // 1
                                { F_LIT(98.0), F_LIT(17.0), F_LIT(34.7), F_LIT(22.0) },     // 0
                                { F_LIT(75.0), F_LIT(21.0), F_LIT(33.3), F_LIT(38.0) },     // 0
                                { F_LIT(187.0), F_LIT(27.0), F_LIT(43.6), F_LIT(53.0) },    // 1
                                { F_LIT(160.0), F_LIT(32.0), F_LIT(30.5), F_LIT(39.0) },    // 1
                                { F_LIT(114.0), F_LIT(17.0), F_LIT(23.8), F_LIT(31.0) },    // 0
                                { F_LIT(123.0), F_LIT(45.0), F_LIT(33.6), F_LIT(34.0) },    // 0
                                { F_LIT(109.0), F_LIT(21.0), F_LIT(42.7), F_LIT(54.0) },    // 0
                                { F_LIT(146.0), F_LIT(27.0), F_LIT(28.9), F_LIT(27.0) },    // 0
                                { F_LIT(111.0), F_LIT(13.0), F_LIT(24.0), F_LIT(23.0) },    // 0
                                { F_LIT(151.0), F_LIT(40.0), F_LIT(41.8), F_LIT(38.0) },    // 1
                                { F_LIT(161.0), F_LIT(27.0), F_LIT(30.4), F_LIT(47.0) },    // 1
                                { F_LIT(140.0), F_LIT(26.0), F_LIT(42.6), F_LIT(24.0) },    // 1
                                { F_LIT(151.0), F_LIT(46.0), F_LIT(42.1), F_LIT(21.0) },    // 1
                                { F_LIT(189.0), F_LIT(25.0), F_LIT(34.3), F_LIT(41.0) },    // 1
                                { F_LIT(107.0), F_LIT(30.0), F_LIT(36.6), F_LIT(25.0) },    // 1
                                { F_LIT(128.0), F_LIT(45.0), F_LIT(40.5), F_LIT(24.0) },    // 1
                                { F_LIT(100.0), F_LIT(60.0), F_LIT(46.8), F_LIT(31.0) },    // 0
                                { F_LIT(93.0), F_LIT(32.0), F_LIT(38.0), F_LIT(23.0) },     // 1
                                { F_LIT(114.0), F_LIT(21.0), F_LIT(27.8), F_LIT(66.0) },    // 0
                                { F_LIT(155.0), F_LIT(27.0), F_LIT(38.7), F_LIT(25.0) },    // 1
                                { F_LIT(111.0), F_LIT(21.0), F_LIT(26.2), F_LIT(23.0) },    // 0
                                { F_LIT(170.0), F_LIT(37.0), F_LIT(34.5), F_LIT(30.0) },    // 1
                                { F_LIT(91.0), F_LIT(21.0), F_LIT(24.2), F_LIT(58.0) },     // 0
                                { F_LIT(106.0), F_LIT(21.0), F_LIT(37.5), F_LIT(26.0) },    // 0
};
