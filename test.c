#include "test.h"

#ifndef DEBUG
#pragma PERSISTENT(X_test)
#pragma PERSISTENT(y_test)
#endif
uint16_t y_test[N_TEST] = { 0,  1,  1,  0,  0,  0,  0,  0,  1,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  0,  0,  0,  0,  1,  0,  0,  0,  1,  1,  0,  0,  1,  1,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  0,  1,  0,  1,  0,  1,  0,  0,  0,  0,  0,  0,  0,  1,  1,  0,  1,  0,  1,  0,  0,  0,  0,  0,  1,  0,  1,  1,  0,  0,  0,  1,  0,  0,  1,  0,  1,  0,  0,  0,  1,  1,  1,  0,  0,  0,  0,  1,  0,  0,  1,  0,  0,  0,  1,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  0,  1,  1,  1,  1,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  0,  1,  0,  0,  0,  0,  1,  1,  0,  1,  0,  1,  1};
fixed X_test[N_TEST][N_FEATURE] = { { F_LIT(44.0), F_LIT(21.0), F_LIT(25.0), F_LIT(36.0) },
			{ F_LIT(152.0), F_LIT(34.0), F_LIT(34.2), F_LIT(33.0) },
			{ F_LIT(112.0), F_LIT(30.0), F_LIT(31.6), F_LIT(25.0) },
			{ F_LIT(61.0), F_LIT(28.0), F_LIT(34.4), F_LIT(46.0) },
			{ F_LIT(95.0), F_LIT(13.0), F_LIT(19.6), F_LIT(25.0) },
			{ F_LIT(102.0), F_LIT(39.0), F_LIT(35.7), F_LIT(28.0) },
			{ F_LIT(103.0), F_LIT(33.0), F_LIT(24.0), F_LIT(33.0) },
			{ F_LIT(100.0), F_LIT(23.0), F_LIT(29.7), F_LIT(21.0) },
			{ F_LIT(152.0), F_LIT(33.0), F_LIT(26.8), F_LIT(43.0) },
			{ F_LIT(100.0), F_LIT(26.0), F_LIT(30.8), F_LIT(21.0) },
			{ F_LIT(91.0), F_LIT(24.0), F_LIT(29.2), F_LIT(21.0) },
			{ F_LIT(78.0), F_LIT(29.0), F_LIT(36.9), F_LIT(21.0) },
			{ F_LIT(88.0), F_LIT(24.0), F_LIT(29.9), F_LIT(23.0) },
			{ F_LIT(97.0), F_LIT(32.0), F_LIT(40.9), F_LIT(32.0) },
			{ F_LIT(132.0), F_LIT(21.0), F_LIT(32.4), F_LIT(21.0) },
			{ F_LIT(92.0), F_LIT(20.0), F_LIT(24.2), F_LIT(28.0) },
			{ F_LIT(101.0), F_LIT(17.0), F_LIT(24.2), F_LIT(23.0) },
			{ F_LIT(122.0), F_LIT(27.0), F_LIT(36.8), F_LIT(27.0) },
			{ F_LIT(100.0), F_LIT(28.0), F_LIT(37.8), F_LIT(24.0) },
			{ F_LIT(128.0), F_LIT(21.0), F_LIT(34.3), F_LIT(24.0) },
			{ F_LIT(103.0), F_LIT(38.0), F_LIT(43.3), F_LIT(33.0) },
			{ F_LIT(191.0), F_LIT(15.0), F_LIT(30.9), F_LIT(34.0) },
			{ F_LIT(83.0), F_LIT(26.0), F_LIT(29.3), F_LIT(36.0) },
			{ F_LIT(82.0), F_LIT(21.0), F_LIT(21.1), F_LIT(25.0) },
			{ F_LIT(131.0), F_LIT(14.0), F_LIT(23.7), F_LIT(21.0) },
			{ F_LIT(129.0), F_LIT(7.0), F_LIT(19.6), F_LIT(60.0) },
			{ F_LIT(175.0), F_LIT(30.0), F_LIT(33.6), F_LIT(38.0) },
			{ F_LIT(100.0), F_LIT(20.0), F_LIT(32.9), F_LIT(28.0) },
			{ F_LIT(112.0), F_LIT(50.0), F_LIT(39.4), F_LIT(24.0) },
			{ F_LIT(90.0), F_LIT(18.0), F_LIT(25.1), F_LIT(25.0) },
			{ F_LIT(122.0), F_LIT(31.0), F_LIT(27.6), F_LIT(45.0) },
			{ F_LIT(105.0), F_LIT(21.0), F_LIT(30.05), F_LIT(24.0) },
			{ F_LIT(163.0), F_LIT(41.0), F_LIT(40.9), F_LIT(47.0) },
			{ F_LIT(110.0), F_LIT(21.0), F_LIT(37.6), F_LIT(30.0) },
			{ F_LIT(118.0), F_LIT(19.0), F_LIT(23.1), F_LIT(46.0) },
			{ F_LIT(99.0), F_LIT(10.0), F_LIT(25.4), F_LIT(21.0) },
			{ F_LIT(158.0), F_LIT(36.0), F_LIT(31.6), F_LIT(28.0) },
			{ F_LIT(171.0), F_LIT(27.0), F_LIT(43.6), F_LIT(26.0) },
			{ F_LIT(98.0), F_LIT(17.0), F_LIT(34.7), F_LIT(22.0) },
			{ F_LIT(75.0), F_LIT(21.0), F_LIT(33.3), F_LIT(38.0) },
			{ F_LIT(187.0), F_LIT(27.0), F_LIT(43.6), F_LIT(53.0) },
			{ F_LIT(160.0), F_LIT(32.0), F_LIT(30.5), F_LIT(39.0) },
			{ F_LIT(114.0), F_LIT(17.0), F_LIT(23.8), F_LIT(31.0) },
			{ F_LIT(123.0), F_LIT(45.0), F_LIT(33.6), F_LIT(34.0) },
			{ F_LIT(109.0), F_LIT(21.0), F_LIT(42.7), F_LIT(54.0) },
			{ F_LIT(146.0), F_LIT(27.0), F_LIT(28.9), F_LIT(27.0) },
			{ F_LIT(111.0), F_LIT(13.0), F_LIT(24.0), F_LIT(23.0) },
			{ F_LIT(151.0), F_LIT(40.0), F_LIT(41.8), F_LIT(38.0) },
			{ F_LIT(161.0), F_LIT(27.0), F_LIT(30.4), F_LIT(47.0) },
			{ F_LIT(140.0), F_LIT(26.0), F_LIT(42.6), F_LIT(24.0) },
			{ F_LIT(151.0), F_LIT(46.0), F_LIT(42.1), F_LIT(21.0) },
			{ F_LIT(189.0), F_LIT(25.0), F_LIT(34.3), F_LIT(41.0) },
			{ F_LIT(107.0), F_LIT(30.0), F_LIT(36.6), F_LIT(25.0) },
			{ F_LIT(128.0), F_LIT(45.0), F_LIT(40.5), F_LIT(24.0) },
			{ F_LIT(100.0), F_LIT(60.0), F_LIT(46.8), F_LIT(31.0) },
			{ F_LIT(93.0), F_LIT(32.0), F_LIT(38.0), F_LIT(23.0) },
			{ F_LIT(114.0), F_LIT(21.0), F_LIT(27.8), F_LIT(66.0) },
			{ F_LIT(155.0), F_LIT(27.0), F_LIT(38.7), F_LIT(25.0) },
			{ F_LIT(111.0), F_LIT(21.0), F_LIT(26.2), F_LIT(23.0) },
			{ F_LIT(170.0), F_LIT(37.0), F_LIT(34.5), F_LIT(30.0) },
			{ F_LIT(91.0), F_LIT(21.0), F_LIT(24.2), F_LIT(58.0) },
			{ F_LIT(106.0), F_LIT(21.0), F_LIT(37.5), F_LIT(26.0) },
			{ F_LIT(179.0), F_LIT(31.0), F_LIT(34.2), F_LIT(60.0) },
			{ F_LIT(87.0), F_LIT(34.0), F_LIT(37.6), F_LIT(24.0) },
			{ F_LIT(100.0), F_LIT(29.0), F_LIT(32.0), F_LIT(42.0) },
			{ F_LIT(91.0), F_LIT(25.0), F_LIT(25.2), F_LIT(23.0) },
			{ F_LIT(137.0), F_LIT(41.0), F_LIT(32.0), F_LIT(39.0) },
			{ F_LIT(150.0), F_LIT(29.0), F_LIT(35.2), F_LIT(54.0) },
			{ F_LIT(131.0), F_LIT(27.0), F_LIT(43.2), F_LIT(26.0) },
			{ F_LIT(87.0), F_LIT(18.0), F_LIT(21.8), F_LIT(21.0) },
			{ F_LIT(179.0), F_LIT(27.0), F_LIT(44.1), F_LIT(23.0) },
			{ F_LIT(107.0), F_LIT(19.0), F_LIT(28.3), F_LIT(29.0) },
			{ F_LIT(164.0), F_LIT(27.0), F_LIT(32.8), F_LIT(45.0) },
			{ F_LIT(154.0), F_LIT(29.0), F_LIT(31.3), F_LIT(37.0) },
			{ F_LIT(133.0), F_LIT(21.0), F_LIT(27.0), F_LIT(36.0) },
			{ F_LIT(100.0), F_LIT(33.0), F_LIT(30.0), F_LIT(46.0) },
			{ F_LIT(124.0), F_LIT(13.0), F_LIT(21.8), F_LIT(21.0) },
			{ F_LIT(130.0), F_LIT(23.0), F_LIT(28.6), F_LIT(21.0) },
			{ F_LIT(162.0), F_LIT(27.0), F_LIT(37.7), F_LIT(52.0) },
			{ F_LIT(110.0), F_LIT(29.0), F_LIT(32.4), F_LIT(27.0) },
			{ F_LIT(134.0), F_LIT(27.0), F_LIT(23.8), F_LIT(60.0) },
			{ F_LIT(147.0), F_LIT(27.0), F_LIT(29.5), F_LIT(50.0) },
			{ F_LIT(144.0), F_LIT(27.0), F_LIT(33.9), F_LIT(40.0) },
			{ F_LIT(100.0), F_LIT(12.0), F_LIT(25.3), F_LIT(28.0) },
			{ F_LIT(102.0), F_LIT(20.0), F_LIT(30.8), F_LIT(26.0) },
			{ F_LIT(172.0), F_LIT(49.0), F_LIT(42.4), F_LIT(28.0) },
			{ F_LIT(94.0), F_LIT(18.0), F_LIT(31.6), F_LIT(23.0) },
			{ F_LIT(85.0), F_LIT(21.0), F_LIT(30.1), F_LIT(35.0) },
			{ F_LIT(171.0), F_LIT(33.0), F_LIT(33.3), F_LIT(24.0) },
			{ F_LIT(147.0), F_LIT(54.0), F_LIT(42.8), F_LIT(24.0) },
			{ F_LIT(163.0), F_LIT(18.0), F_LIT(31.6), F_LIT(28.0) },
			{ F_LIT(151.0), F_LIT(38.0), F_LIT(29.7), F_LIT(36.0) },
			{ F_LIT(87.0), F_LIT(27.0), F_LIT(34.6), F_LIT(22.0) },
			{ F_LIT(106.0), F_LIT(21.0), F_LIT(25.8), F_LIT(27.0) },
			{ F_LIT(190.0), F_LIT(27.0), F_LIT(35.5), F_LIT(66.0) },
			{ F_LIT(121.0), F_LIT(27.0), F_LIT(36.0), F_LIT(25.0) },
			{ F_LIT(112.0), F_LIT(27.0), F_LIT(37.8), F_LIT(41.0) },
			{ F_LIT(106.0), F_LIT(54.0), F_LIT(36.6), F_LIT(45.0) },
			{ F_LIT(137.0), F_LIT(21.0), F_LIT(24.2), F_LIT(55.0) },
			{ F_LIT(129.0), F_LIT(28.0), F_LIT(35.9), F_LIT(39.0) },
			{ F_LIT(106.0), F_LIT(18.0), F_LIT(22.7), F_LIT(48.0) },
			{ F_LIT(164.0), F_LIT(21.0), F_LIT(30.8), F_LIT(32.0) },
			{ F_LIT(111.0), F_LIT(21.0), F_LIT(24.6), F_LIT(31.0) },
			{ F_LIT(133.0), F_LIT(15.0), F_LIT(32.4), F_LIT(37.0) },
			{ F_LIT(173.0), F_LIT(33.0), F_LIT(35.7), F_LIT(22.0) },
			{ F_LIT(99.0), F_LIT(19.0), F_LIT(25.6), F_LIT(24.0) },
			{ F_LIT(81.0), F_LIT(41.0), F_LIT(46.3), F_LIT(32.0) },
			{ F_LIT(125.0), F_LIT(24.0), F_LIT(24.3), F_LIT(25.0) },
			{ F_LIT(169.0), F_LIT(19.0), F_LIT(29.9), F_LIT(31.0) },
			{ F_LIT(105.0), F_LIT(41.0), F_LIT(41.5), F_LIT(22.0) },
			{ F_LIT(174.0), F_LIT(37.0), F_LIT(44.5), F_LIT(24.0) },
			{ F_LIT(143.0), F_LIT(23.0), F_LIT(42.4), F_LIT(22.0) },
			{ F_LIT(137.0), F_LIT(27.0), F_LIT(27.3), F_LIT(59.0) },
			{ F_LIT(114.0), F_LIT(21.0), F_LIT(21.9), F_LIT(37.0) },
			{ F_LIT(112.0), F_LIT(22.0), F_LIT(25.0), F_LIT(24.0) },
			{ F_LIT(108.0), F_LIT(10.0), F_LIT(25.3), F_LIT(22.0) },
			{ F_LIT(114.0), F_LIT(21.0), F_LIT(24.9), F_LIT(57.0) },
			{ F_LIT(123.0), F_LIT(32.0), F_LIT(42.1), F_LIT(26.0) },
			{ F_LIT(103.0), F_LIT(21.0), F_LIT(24.3), F_LIT(29.0) },
			{ F_LIT(149.0), F_LIT(29.0), F_LIT(29.3), F_LIT(42.0) },
			{ F_LIT(133.0), F_LIT(21.0), F_LIT(40.2), F_LIT(37.0) },
			{ F_LIT(81.0), F_LIT(15.0), F_LIT(30.1), F_LIT(25.0) },
			{ F_LIT(139.0), F_LIT(21.0), F_LIT(27.1), F_LIT(57.0) },
			{ F_LIT(122.0), F_LIT(27.0), F_LIT(33.3), F_LIT(33.0) },
			{ F_LIT(151.0), F_LIT(32.0), F_LIT(42.9), F_LIT(36.0) },
			{ F_LIT(181.0), F_LIT(42.0), F_LIT(40.0), F_LIT(22.0) },
			{ F_LIT(95.0), F_LIT(25.0), F_LIT(35.0), F_LIT(43.0) },
			{ F_LIT(152.0), F_LIT(39.0), F_LIT(41.5), F_LIT(27.0) },
			{ F_LIT(91.0), F_LIT(32.0), F_LIT(39.9), F_LIT(25.0) },
			{ F_LIT(99.0), F_LIT(17.0), F_LIT(25.6), F_LIT(28.0) },
			{ F_LIT(128.0), F_LIT(39.0), F_LIT(36.5), F_LIT(37.0) },
			{ F_LIT(91.0), F_LIT(21.0), F_LIT(35.6), F_LIT(68.0) },
			{ F_LIT(96.0), F_LIT(13.0), F_LIT(21.1), F_LIT(26.0) },
			{ F_LIT(80.0), F_LIT(11.0), F_LIT(30.0), F_LIT(22.0) },
			{ F_LIT(88.0), F_LIT(11.0), F_LIT(24.8), F_LIT(22.0) },
			{ F_LIT(97.0), F_LIT(23.0), F_LIT(28.2), F_LIT(22.0) },
			{ F_LIT(103.0), F_LIT(30.0), F_LIT(27.6), F_LIT(27.0) },
			{ F_LIT(139.0), F_LIT(21.0), F_LIT(25.6), F_LIT(29.0) },
			{ F_LIT(120.0), F_LIT(27.0), F_LIT(30.0), F_LIT(38.0) },
			{ F_LIT(85.0), F_LIT(21.0), F_LIT(39.6), F_LIT(27.0) },
			{ F_LIT(143.0), F_LIT(22.0), F_LIT(26.2), F_LIT(21.0) },
			{ F_LIT(94.0), F_LIT(27.0), F_LIT(43.5), F_LIT(21.0) },
			{ F_LIT(128.0), F_LIT(41.0), F_LIT(32.0), F_LIT(33.0) },
			{ F_LIT(119.0), F_LIT(21.0), F_LIT(25.2), F_LIT(37.0) },
			{ F_LIT(135.0), F_LIT(46.0), F_LIT(40.6), F_LIT(26.0) },
			{ F_LIT(89.0), F_LIT(21.0), F_LIT(22.5), F_LIT(33.0) },
			{ F_LIT(107.0), F_LIT(20.0), F_LIT(24.7), F_LIT(22.0) },
			{ F_LIT(166.0), F_LIT(19.0), F_LIT(25.8), F_LIT(51.0) },
			{ F_LIT(119.0), F_LIT(39.0), F_LIT(45.6), F_LIT(29.0) },
			{ F_LIT(158.0), F_LIT(21.0), F_LIT(29.8), F_LIT(63.0) },
			{ F_LIT(131.0), F_LIT(27.0), F_LIT(31.6), F_LIT(32.0) },
			{ F_LIT(114.0), F_LIT(34.0), F_LIT(44.2), F_LIT(27.0) },
			{ F_LIT(80.0), F_LIT(31.0), F_LIT(34.2), F_LIT(27.0) },
			{ F_LIT(129.0), F_LIT(36.0), F_LIT(41.2), F_LIT(38.0) } };
