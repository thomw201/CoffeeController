PRAGMA foreign_keys=OFF;
BEGIN TRANSACTION;
CREATE TABLE Statistics (Runningtime TIME, TotalWater INTEGER, avgTemp INTEGER);
CREATE TABLE logType (ID INTEGER PRIMARY KEY DEFAULT AUTO_INCREMENT, Type INTEGER NOT NULL);
INSERT INTO "logType" VALUES(1,'Info');
INSERT INTO "logType" VALUES(2,'Warning');
INSERT INTO "logType" VALUES(3,'Error');
INSERT INTO "logType" VALUES(4,'Debug');
CREATE TABLE Log (ID INTEGER PRIMARY KEY NOT NULL DEFAULT AUTO_INCREMENT, Time TIMESTAMP DEFAULT (datetime('now', 'localtime')) NOT NULL, Type INTEGER NOT NULL REFERENCES logType (ID), Message CHAR (50), Water INTEGER, "Temp" DECIMAL (4, 2), LED1 INTEGER, LED2 INTEGER, Sound BOOLEAN);
INSERT INTO "Log" VALUES(255,'2015-11-29 02:10:46',1,'Succesfully started on Sun Nov 29 02:10:46 2015
',9,0,0,0,0);
INSERT INTO "Log" VALUES(256,'2015-11-29 02:12:19',1,' profiles loaded.',9,0,0,0,1);
INSERT INTO "Log" VALUES(257,'2015-11-29 02:13:10',1,'rofiles loaded.',9,0,0,0,1);
INSERT INTO "Log" VALUES(258,'2015-11-29 02:13:14',1,'Succesfully started on Sun Nov 29 02:13:14 2015
',9,0,0,0,0);
INSERT INTO "Log" VALUES(259,'2015-11-29 02:14:17',1,'rofiles loaded.',9,0,0,0,1);
INSERT INTO "Log" VALUES(260,'2015-11-29 02:14:21',1,'Succesfully started on Sun Nov 29 02:14:21 2015
',9,0,0,0,0);
INSERT INTO "Log" VALUES(261,'2015-11-29 02:16:13',1,'rofiles loaded.',9,0,0,0,1);
INSERT INTO "Log" VALUES(262,'2015-11-29 02:16:16',1,'Succesfully started on Sun Nov 29 02:16:16 2015
',9,0,0,0,0);
INSERT INTO "Log" VALUES(263,'2015-11-29 02:17:32',1,'rofiles loaded.',9,0,0,0,1);
INSERT INTO "Log" VALUES(264,'2015-11-29 02:17:35',1,'Succesfully started on Sun Nov 29 02:17:35 2015
',9,0,0,0,0);
INSERT INTO "Log" VALUES(265,'2015-11-29 04:22:16',1,'rofiles loaded.',9,0,0,0,1);
INSERT INTO "Log" VALUES(266,'2015-11-29 04:26:22',1,'rofiles loaded.',9,0,0,0,1);
INSERT INTO "Log" VALUES(267,'2015-11-29 04:27:06',1,'rofiles loaded.',15,0,0,0,1);
INSERT INTO "Log" VALUES(268,'2015-11-29 04:30:45',1,'rofiles loaded.',9,0,0,0,1);
INSERT INTO "Log" VALUES(269,'2015-11-29 04:30:48',1,'Succesfully started on Sun Nov 29 04:30:48 2015
',9,0,0,0,0);
INSERT INTO "Log" VALUES(270,'2015-11-29 04:30:53',1,'rofiles loaded.',9,0,0,0,1);
INSERT INTO "Log" VALUES(271,'2015-11-29 04:30:56',1,'rofiles loaded.',9,0,0,0,1);
INSERT INTO "Log" VALUES(272,'2015-11-29 04:30:57',1,'rofiles loaded.',9,0,0,0,1);
INSERT INTO "Log" VALUES(273,'2015-11-29 04:31:00',1,'rofiles loaded.',9,0,0,0,1);
INSERT INTO "Log" VALUES(274,'2015-11-29 04:32:24',1,'rofiles loaded.',9,0,0,0,1);
INSERT INTO "Log" VALUES(275,'2015-11-29 04:32:28',1,'rofiles loaded.',9,0,0,0,1);
INSERT INTO "Log" VALUES(276,'2015-11-29 04:32:32',1,'rofiles loaded.',9,0,0,0,1);
INSERT INTO "Log" VALUES(277,'2015-11-29 04:39:26',1,'rofiles loaded.',9,0,0,0,1);
INSERT INTO "Log" VALUES(278,'2015-11-29 04:39:29',1,'Succesfully started on Sun Nov 29 04:39:29 2015
',9,0,0,0,0);
INSERT INTO "Log" VALUES(279,'2015-11-30 00:22:14',1,'rofiles loaded.',9,0,0,0,1);
INSERT INTO "Log" VALUES(280,'2015-11-30 00:22:14',1,'Succesfully started on Mon Nov 30 00:22:14 2015
',9,0,0,0,0);
INSERT INTO "Log" VALUES(281,'2015-11-30 00:22:46',1,'rofiles loaded.',9,0,0,0,1);
INSERT INTO "Log" VALUES(282,'2015-11-30 00:22:46',1,'Succesfully started on Mon Nov 30 00:22:46 2015
',9,0,0,0,0);
INSERT INTO "Log" VALUES(283,'2015-11-30 00:23:14',1,'rofiles loaded.',9,0,0,0,1);
INSERT INTO "Log" VALUES(284,'2015-11-30 00:23:14',1,'Succesfully started on Mon Nov 30 00:23:14 2015
',9,0,0,0,0);
INSERT INTO "Log" VALUES(285,'2015-11-30 00:23:35',1,'rofiles loaded.',9,0,0,0,1);
INSERT INTO "Log" VALUES(286,'2015-11-30 00:23:35',1,'Succesfully started on Mon Nov 30 00:23:35 2015
',9,0,0,0,0);
INSERT INTO "Log" VALUES(287,'2015-11-30 00:23:49',1,'rofiles loaded.',9,0,0,0,1);
INSERT INTO "Log" VALUES(288,'2015-11-30 00:23:49',1,'Succesfully started on Mon Nov 30 00:23:49 2015
',9,0,0,0,0);
INSERT INTO "Log" VALUES(289,'2015-11-30 00:25:40',1,'rofiles loaded.',9,0,0,0,1);
INSERT INTO "Log" VALUES(290,'2015-11-30 00:25:40',1,'Succesfully started on Mon Nov 30 00:25:40 2015
',9,0,0,0,0);
INSERT INTO "Log" VALUES(291,'2015-11-30 00:25:44',1,'rofiles loaded.',8,0,0,0,1);
INSERT INTO "Log" VALUES(292,'2015-11-30 00:25:44',1,'Succesfully started on Mon Nov 30 00:25:44 2015
',8,0,0,0,0);
INSERT INTO "Log" VALUES(294,'2015-11-30 00:25:47',1,'Succesfully started on Mon Nov 30 00:25:47 2015
',9,0,0,0,0);
INSERT INTO "Log" VALUES(295,'2015-11-30 00:25:55',1,'rofiles loaded.',9,0,0,0,1);
INSERT INTO "Log" VALUES(296,'2015-11-30 00:25:55',1,'Succesfully started on Mon Nov 30 00:25:55 2015
',9,0,0,0,0);
INSERT INTO "Log" VALUES(297,'2015-11-30 00:26:03',1,'rofiles loaded.',9,0,0,0,1);
INSERT INTO "Log" VALUES(298,'2015-11-30 00:26:03',1,'Succesfully started on Mon Nov 30 00:26:03 2015
',9,0,0,0,0);
INSERT INTO "Log" VALUES(299,'2015-11-30 00:30:18',1,'rofiles loaded.',9,0,0,0,1);
INSERT INTO "Log" VALUES(300,'2015-11-30 00:30:18',1,'Succesfully started on Mon Nov 30 00:30:18 2015
',9,0,0,0,0);
INSERT INTO "Log" VALUES(301,'2015-11-30 00:30:28',1,'rofiles loaded.',9,0,0,0,1);
INSERT INTO "Log" VALUES(302,'2015-11-30 00:30:28',1,'Succesfully started on Mon Nov 30 00:30:28 2015
',9,0,0,0,0);
INSERT INTO "Log" VALUES(303,'2015-11-30 00:30:40',1,'rofiles loaded.',9,0,0,0,1);
INSERT INTO "Log" VALUES(304,'2015-11-30 00:30:40',1,'Succesfully started on Mon Nov 30 00:30:40 2015
',9,0,0,0,0);
INSERT INTO "Log" VALUES(305,'2015-12-01 00:59:09',1,'rofiles loaded.',9,0,0,0,1);
INSERT INTO "Log" VALUES(306,'2015-12-01 00:59:09',1,'Succesfully started on Tue Dec  1 00:59:09 2015
',9,0,0,0,0);
INSERT INTO "Log" VALUES(307,'2015-12-01 01:12:22',1,'rofiles loaded.',8,0,0,0,1);
INSERT INTO "Log" VALUES(308,'2015-12-01 01:12:22',1,'Succesfully started on Tue Dec  1 01:12:22 2015
',8,0,0,0,0);
/**** ERROR: (11) database disk image is malformed *****/
/**** ERROR: (11) database disk image is malformed *****/
CREATE TABLE Days (ID INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE NOT NULL, Monday BOOLEAN DEFAULT (0), Tuesday BOOLEAN DEFAULT (0), Wednesday BOOLEAN DEFAULT (0), Thursday BOOLEAN DEFAULT (0), Friday BOOLEAN DEFAULT (0), Saturday BOOLEAN DEFAULT (0), Sunday BOOLEAN DEFAULT (0), Everyday BOOLEAN DEFAULT (0));
INSERT INTO "Days" VALUES(17,0,0,0,0,0,0,0,0);
INSERT INTO "Days" VALUES(18,1,0,0,0,0,0,0,0);
INSERT INTO "Days" VALUES(19,0,1,1,0,0,0,0,0);
INSERT INTO "Days" VALUES(20,0,0,1,0,0,0,0,0);
INSERT INTO "Days" VALUES(21,0,0,0,0,0,0,0,1);
INSERT INTO "Days" VALUES(22,0,0,0,0,0,0,0,0);
INSERT INTO "Days" VALUES(23,0,0,0,0,0,0,0,0);
INSERT INTO "Days" VALUES(24,0,0,0,0,0,0,1,1);
INSERT INTO "Days" VALUES(25,0,0,0,0,0,0,1,0);
INSERT INTO "Days" VALUES(26,0,0,0,0,0,0,0,1);
INSERT INTO "Days" VALUES(27,1,0,0,0,0,0,0,0);
INSERT INTO "Days" VALUES(28,0,0,0,0,0,0,0,1);
INSERT INTO "Days" VALUES(29,0,0,0,0,0,0,1,0);
CREATE TABLE Profiles (ID INTEGER PRIMARY KEY UNIQUE NOT NULL, Name TEXT NOT NULL, DaysID INTEGER REFERENCES Days (ID) ON DELETE SET NULL MATCH FULL, Starttime TIME NOT NULL, Stayonfor INTEGER NOT NULL, Active BOOLEAN NOT NULL);
INSERT INTO "Profiles" VALUES(6,'Dinsdag',19,1300,60,0);
INSERT INTO "Profiles" VALUES(7,'Zondag',25,2006,15,0);
INSERT INTO "Profiles" VALUES(8,'Ochtendkoffie',26,830,30,0);
INSERT INTO "Profiles" VALUES(9,'Coffee!',27,1050,5,1);
DELETE FROM sqlite_sequence;
INSERT INTO "sqlite_sequence" VALUES('Days',29);
COMMIT;
