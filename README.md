# DB_C
CC ESGI Michaël Rossignol 3si5 
Pour compilé :  gcc -o db.exe  main.c table.c statement.c
IDE : Visual studio code
compilateur : minGW
Fichier binaire pour stocker les informations rentées dans la base de données
Toute les commandes sont en minuscule


Pour l'aide dans le programme :

Pour sortir du progamme .exit 
Pour avoir une aide .help
Pour voir combien de slot est utilisé .status


Pour l'utilisation de la base de données :
Les commandes : insert, show, delete, update
On ajoute la commande que l'on shouaite utiliser (insert, show, delete) puis un prompt nous indique les informations à renseigner. 

Insert :
Pour l'ID il faut obligatoirement un chiffre
Pour l'email il faut obligatoirement un @ 

Show:
Aucun argument

Delete:
Pour supprimer une ligne il nous faut l'ID
Pour supprimer la table, il faut supprimer le database.db qui se trouve dans le répertoire

Update:
Remplace une ligne existante en redemandant les informations 


Pour les capacités de stockage de la base de données :

32 caractères pour le nom d'utilisateur
255 caractères pour l'email
1000 lignes maximum dans la table