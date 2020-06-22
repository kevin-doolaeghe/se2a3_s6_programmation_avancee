https://git-scm.com/

★ Afficher l'aide
   → git help [-a]
   → git

★ Définir le nom d'utilisateur et son email
   → git config --global user.name "Nom"
   → git config --global user.email "E-mail"

★ Afficher les logs
   → git log <option>
       → -(n) : Afficher les n derniers commits
       → --since, --after : Afficher les commits après une date
       → --until, --before : Afficher les commits avant une date
       → --author : Afficher les commits d'un auteur
       → -S : Afficher les commits contenant la chaîne de caractères

★ Afficher le statut du dépôt
   → git status

★ Afficher les modifications qui ne sont pas encore indexées
   → git diff

★ Initialiser un dépôt
   → git init

★ Ajouter des fichiers au suivi de version
   → git add <fichier>
   → git add *

★ Effacer des fichiers indexés
   → git rm <fichier>

★ Déplacer des fichiers
   → git mv <src> <dst>

★ Ignorer des fichiers
   → Créer un fichier .gitignore
   → Renseigner les fichiers ou la forme des fichiers

★ Faire un commit
   → git commit -a -m "message"

★ Ajouter une branche
   → git branch <branche>

★ Supprimer une branche
   → git branch -d <branche>

★ Changer de branche
   → git checkout <branche>

★ Fusionner deux branches
   → git checkout <dst>
   → git merge <src> [--no-ff]

★ Cloner un dépôt distant
   → git clone <url>
   → git clone <url> --branch <branche>

★ Afficher la liste des dépôts distants enregistrés
   → git remote

★ Ajouter un dépôt distant
   → git remote add <nom> <url>

★ Renommer un dépôt distant
   → git remote rename <ancien> <nouveau>

★ Récupérer les informations sans les ajouter à la branche courante
   → git fetch <nom>

★ Récupérer les information et les ajouter à la branche courante
   → git pull origin <branch>

★ Pousser son travail sur un dépôt distant
   → git push origin <branch>
   → La branche par défaut est master

★ Inspecter un dépôt distant
   → git remote show [n]
