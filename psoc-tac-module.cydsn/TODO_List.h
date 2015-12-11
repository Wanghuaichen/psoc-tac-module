/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
/*
À faire :

To do       Done
            1- Modifier la fonction de calibration pour calibrer soit le module 1, soit le module 2.
2- Changer le CAN ID du message à renvoyer au master dans la fonction « treatmessage » du fichier CAN_Communication.c .
            3- Changer les fonctions d’interaction avec l’EEPROM pour qu’elles traitent des int16 au lieu des int32.
4- Terminer la fonction getThermistorTemp(moduleNumber) et ajouter les thermistors manquants au projet.
            5- Modifier la fonction d’enregistrement et de lecture de l’EEPROM pour être capable de gérer la calibration de différents modules.
6- Modifier les fonctions de l’EEPROM pour pouvoir ajouter le ID unique de notre microcontrôleur.
            7- Écrire la fonction de maintien de la température pour gérer les deux TAC en même temps et être capable de stopper l’une ou l’autre par un message indiquant de le faire directement dans l’interrupt de message reçu sur le bus CAN. (Voir procédé de la fonction Stop_Calibration et s’en inspirer)
            8- Changer la fonction peltierControl pour qu'elle tire profit de la table de calibration existante.
            9- Modifier la fonction getThermistorTemp pour qu'elle retourne la température du thermistor désiré
            10- Tester la fonction getSubModuleThermistorTemp.
11- Ajouter une option pour enregistrer et retrouver 5 (environ) valeurs dans l'EEPROM pour les polynômes de la lecture de turbidité. (table de calibration de turbidité)
12- Trouver les pins pour mettre les photodiodes et les DEL pour la lecture de turbidité.
13- Terminer la "Black Box" pour le CAN.
            14- Modifier la fonction treatMessage, section SEND_TEMPERATURE pour quelle retourne la température du thermistor désiré.
            15- Terminer d'écrire la fonction void updatePeltierOutput(Tac_Submodule* TACPtr) ***********
            16- Updater les fonctions d'écriture dans l'eeprom pour prendre en compte lequel des deux sous-modules on veut traiter.
17- Ajouter que lorsque l'on change la target temperature, le pwmFromCalibrationStatus des Tac_submodule passe à Outdated. (Permettre de changer la target temperature
//  uniquement lorsque le temperature_mode est à waiting.
18- Remplacer dans la ligne suivante "toSend.CAN_ID = TEMP_CAN_ID;" le ID pour MASTER_ID dans le fichier CAN_1_TX_RX_func.c.
19- Décommenter la ligne qui empêche l'interrupt pour la lecture de turbidité de se faire dans la fonction initTacModule();
20- Ajouter une fonction pour udpater la température ambiante et l'utiliser lorsque l'on reçoit la commande pour commencer à maintenir une température.
*/

/* [] END OF FILE */
