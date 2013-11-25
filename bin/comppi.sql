/* This file was generated by ODB, object-relational mapping (ORM)
 * compiler for C++.
 */

DROP TABLE IF EXISTS `ProteinNameMap`;

DROP TABLE IF EXISTS `NameToProtein`;

DROP TABLE IF EXISTS `ProtLocToSystemType`;

DROP TABLE IF EXISTS `ProteinToLocalization`;

DROP TABLE IF EXISTS `SystemType`;

DROP TABLE IF EXISTS `InteractionToSystemType`;

DROP TABLE IF EXISTS `Interaction`;

DROP TABLE IF EXISTS `Protein`;

CREATE TABLE `Protein` (
  `id` INT UNSIGNED NOT NULL PRIMARY KEY AUTO_INCREMENT,
  `specieId` INT NOT NULL,
  `proteinName` VARCHAR(255) NOT NULL,
  `proteinNamingConvention` VARCHAR(255) NOT NULL)
 ENGINE=InnoDB;

CREATE INDEX `search_idx`
  ON `Protein` (
    `proteinName`,
    `proteinNamingConvention`,
    `specieId`);

CREATE INDEX `species_idx`
  ON `Protein` (`specieId`);

CREATE TABLE `Interaction` (
  `id` INT UNSIGNED NOT NULL PRIMARY KEY AUTO_INCREMENT,
  `actorAId` INT UNSIGNED,
  `actorBId` INT UNSIGNED,
  `sourceDb` VARCHAR(255) NOT NULL,
  `pubmedId` INT NOT NULL

  /*
  CONSTRAINT `Interaction_actorAId_fk`
    FOREIGN KEY (`actorAId`)
    REFERENCES `Protein` (`id`)
  */

  /*
  CONSTRAINT `Interaction_actorBId_fk`
    FOREIGN KEY (`actorBId`)
    REFERENCES `Protein` (`id`)
  */)
 ENGINE=InnoDB;

CREATE INDEX `search_idx_aid`
  ON `Interaction` (`actorAId`);

CREATE INDEX `search_idx_bid`
  ON `Interaction` (`actorBId`);

CREATE INDEX `single_interaction_per_source`
  ON `Interaction` (
    `actorAId`,
    `actorBId`,
    `sourceDb`);

CREATE TABLE `InteractionToSystemType` (
  `interactionId` INT UNSIGNED NOT NULL,
  `systemTypeId` INT UNSIGNED NOT NULL,

  CONSTRAINT `InteractionToSystemType_interactionId_fk`
    FOREIGN KEY (`interactionId`)
    REFERENCES `Interaction` (`id`)
    ON DELETE CASCADE)
 ENGINE=InnoDB;

CREATE INDEX `interactionId_i`
  ON `InteractionToSystemType` (`interactionId`);

CREATE TABLE `SystemType` (
  `id` INT UNSIGNED NOT NULL PRIMARY KEY AUTO_INCREMENT,
  `name` VARCHAR(255) NOT NULL,
  `confidenceType` INT NOT NULL)
 ENGINE=InnoDB;

CREATE INDEX `search_idx`
  ON `SystemType` (`name`);

CREATE TABLE `ProteinToLocalization` (
  `id` INT UNSIGNED NOT NULL PRIMARY KEY AUTO_INCREMENT,
  `proteinId` INT UNSIGNED,
  `localizationId` INT NOT NULL,
  `sourceDb` VARCHAR(255) NOT NULL,
  `pubmedId` INT NOT NULL

  /*
  CONSTRAINT `ProteinToLocalization_proteinId_fk`
    FOREIGN KEY (`proteinId`)
    REFERENCES `Protein` (`id`)
  */)
 ENGINE=InnoDB;

CREATE INDEX `search_idx`
  ON `ProteinToLocalization` (`proteinId`);

CREATE INDEX `single_loc_per_source`
  ON `ProteinToLocalization` (
    `proteinId`,
    `localizationId`,
    `sourceDb`);

CREATE TABLE `ProtLocToSystemType` (
  `protLocId` INT UNSIGNED NOT NULL,
  `systemTypeId` INT UNSIGNED NOT NULL,

  CONSTRAINT `ProtLocToSystemType_protLocId_fk`
    FOREIGN KEY (`protLocId`)
    REFERENCES `ProteinToLocalization` (`id`)
    ON DELETE CASCADE

  /*
  CONSTRAINT `ProtLocToSystemType_systemTypeId_fk`
    FOREIGN KEY (`systemTypeId`)
    REFERENCES `SystemType` (`id`)
  */)
 ENGINE=InnoDB;

CREATE INDEX `protLocId_i`
  ON `ProtLocToSystemType` (`protLocId`);

CREATE TABLE `NameToProtein` (
  `id` INT UNSIGNED NOT NULL PRIMARY KEY AUTO_INCREMENT,
  `specieId` INT NOT NULL,
  `name` VARCHAR(255) NOT NULL,
  `namingConvention` VARCHAR(255) NOT NULL,
  `proteinId` INT UNSIGNED

  /*
  CONSTRAINT `NameToProtein_proteinId_fk`
    FOREIGN KEY (`proteinId`)
    REFERENCES `Protein` (`id`)
  */)
 ENGINE=InnoDB;

CREATE INDEX `search_idx`
  ON `NameToProtein` (
    `name`,
    `namingConvention`,
    `specieId`);

CREATE INDEX `synonym_idx`
  ON `NameToProtein` (`proteinId`);

CREATE TABLE `ProteinNameMap` (
  `id` INT UNSIGNED NOT NULL PRIMARY KEY AUTO_INCREMENT,
  `specieId` INT NOT NULL,
  `namingConventionA` VARCHAR(255) NOT NULL,
  `proteinNameA` VARCHAR(255) NOT NULL,
  `namingConventionB` VARCHAR(255) NOT NULL,
  `proteinNameB` VARCHAR(255) NOT NULL)
 ENGINE=InnoDB;

CREATE INDEX `search_idx`
  ON `ProteinNameMap` (
    `proteinNameA`,
    `namingConventionA`,
    `specieId`);

CREATE INDEX `reverse_search_idx`
  ON `ProteinNameMap` (
    `proteinNameB`,
    `namingConventionB`,
    `specieId`);

CREATE INDEX `unique_translation`
  ON `ProteinNameMap` (
    `proteinNameA`,
    `proteinNameB`,
    `namingConventionA`,
    `namingConventionB`,
    `specieId`);

/*
ALTER TABLE `InteractionToSystemType` ADD
  CONSTRAINT `InteractionToSystemType_systemTypeId_fk`
    FOREIGN KEY (`systemTypeId`)
    REFERENCES `SystemType` (`id`)
*/

