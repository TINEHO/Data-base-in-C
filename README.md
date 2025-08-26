🗄️ DB en C
Mini base de données en C

 Il s'agit d'une implémentation simple d'une base de données permettant d'insérer, afficher, mettre à jour et supprimer des entrées via des commandes en ligne.

⚙️ Configuration
Compilation
Pour compiler le programme, utilisez la commande suivante :

gcc -o db.exe main.c table.c statement.c

Environnement de Développement
IDE : Visual Studio Code
Compilateur : MinGW

Stockage
Les informations sont stockées dans un fichier binaire pour une gestion persistante des données.

🛠️ Commandes Principales
Pour obtenir de l'aide dans le programme
Quitter le programme : .exit
Afficher l'aide : .help
Vérifier l'utilisation des slots : .status
Gestion des données
Voici les commandes disponibles pour manipuler les données :

insert : Ajouter une entrée dans la base.

ID : doit être un chiffre.
Email : doit contenir un @.
show : Afficher toutes les données de la table.

Aucun argument requis.
delete : Supprimer une ligne ou toute la table.

Pour une ligne : spécifiez l'ID de la ligne à supprimer.
Pour toute la table : supprimez manuellement le fichier database.db dans le répertoire.
update : Mettre à jour une ligne existante.

Remplace les données d'une ligne en demandant de nouvelles informations.
💾 Capacités de Stockage
Nom d'utilisateur : 32 caractères maximum
Email : 255 caractères maximum
Nombre de lignes : 1 000 lignes maximum
📚 Utilisation
Lancez le programme après compilation.
Tapez une commande parmi insert, show, delete, ou update.
Suivez les instructions affichées dans le terminal pour insérer ou manipuler les données.
🧑‍💻 Auteur
TINEHO

