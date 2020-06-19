# Exemple de Projet avec Intégration Continue

![Pipeline](https://gitlab.com/jeremie.dequidt/ima_prog_adv/badges/master/pipeline.svg) ![Coverage](https://gitlab.com/jeremie.dequidt/ima_prog_adv/badges/master/coverage.svg)

Ce dépôt `GitLab` contient un exemple de projet `C` pour lequel la compilation, les tests... ont été automatisés. Vous pouvez cloner ce dépôt et l'adapter à vos besoins.

Le code métier de ce projet se base sur les algorithmes de tris vus en programmation au S5. Il sert juste à illustrer le _pipeline_ d'intégration continue.

## Contenu du dépôt

- `README.md` le fichier que vous être en train de lire
- `Makefile` permet la compilation du code métier (cible `main`) et des tests unitaires (cible `tests`)
- `.clang-format` contient les règles de formatage de code
- `.gitlab-ci.yaml` contient la description du _pipeline_ d'intégration continue
- le répertoire `includes` contient les déclarations de fonctions
- le répertoire `src` contient les sources du projet
- le répertoire `tests` contient le fichier `.c` qui permet de réaliser les tests unitaires
- le répertoire `scripts` contient un script python qui permet de vérifier le formatage sur tous les fichiers
- le répertoire `hooks` contient un script qui s'assure _en local_ que les fichiers respectent bien le formatage. Il suffit de les copier dans votre répertoire `.git/hooks/`

## Le fichier `Makefile`

Un fichier `Makefile` assez classique mais pour lequel il a fallu ajouter des options de compilation `-fprofile-arcs -ftest-coverage` et d'édition de liens `--coverage` ce qui va permettre de déterminer la couverture des tests unitaires.

Pour les tests unitaires, il est important d'ajouter la bibliothèque `check` et ses dépendences `rt` et `subunit`

## Le fichier `unit_tests.c`

Il se base sur la bibliothèque [check](https://libcheck.github.io/check/). Le principe est de définir des tests unitaires sur le principe suivant:

~~~
START_TEST (nom_du_test)
{
    // déclaration et initialisation de variables
    // appel de la fonction à tester
    // test du résultat de la fonction avec ck_assert
}
END_TEST
~~~

Ces tests font ensuite partie d'une suite de tests

~~~
Suite *nom_suite (void)
{
    Suite *s       = suite_create ("Nom de la suite");
    TCase *tc_core = tcase_create ("Core");

    tcase_add_test (tc_core, nom_du_test);
    // ajout d'autres tests unitaires
    //...

    suite_add_tcase (s, tc_core);
    return s;
}
~~~

qui peut être lancée par un `runner`

~~~
int main (void)
{
    int      no_failed = 0;
    Suite *  s         = nom_suite ();
    SRunner *runner    = srunner_create (s);
    srunner_run_all (runner, CK_NORMAL);
    no_failed = srunner_ntests_failed (runner);
    srunner_free (runner);
    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
~~~

et qui a l'exécution va indiquer le nombre de tests réussis ou échoués.

## Le fichier `.gitlab-ci.yaml`

Ce fichier exécute un certain nombre de commandes lorsqu'un `commit` est fait sur le dépôt.

### Configuration

Étant donné que la machine qui va compiler le code est une machine virtuelle qui est détruite après chaque compilation, il faut lui préciser quelles sont les dépendances ou paquets requis. Pour cela on utilise la directive `before-script`

~~~
before_script:
    - apt-get update -y
    - apt-get upgrade -y
    - apt-get install -y clang-format clang-tidy clang-tools clang make check cppcheck libcppunit-subunit-dev lcov llvm # ajout de toutes les dépendances
~~~

### Définition des étapes du pipeline

L'intégration fonctionne en mode `pipeline` il s'agit d'une succession de phases qui sont exécutées en cascade. Si une étape échoue (et sauf conditions particulières), le pipeline s'arrête.

Ces différentes phases sont listées après la clé `stages`. Dans cet exemple, il y a six étapes:

~~~
stages:
    - codestyling   # vérifie le formatage des sources
    - check         # analyse statique du code
    - build         # compilation
    - test          # tests unitaires
    - coverage      # calcul de la couverture de codes des tests unitaires
    - clean         # suppression des fichiers temporaires
~~~

Chaque étape peut contenir un certain nombre de tâches qui peuvent être exécutées en parallèle. Chaque tâche est construite sur le modèle suivant:

~~~
nom_de_la_tache:
    stage: nom_de_l_etape
    script: # instructions à exécuter
        - instruction_1_a_executer
        - instruction_2_a_executer
        - ...
    when: on_success # ne s'effectue que si l'étape précédente a réussi
    dependencies:
        - tache_dependante
    artifacts:
        paths:
            - chemin/ # endroit où seront stockés des fichiers à conserver
~~~

- Il est possible de spécifier que les tâches s'exécutent obligatoirement même si l'étape précédente à échouer avec `when: always`
- Sur le même principe, on peut utiliser `allow_failure: true` pour permettre à une tâche d'échouer sans arrêter le pipeline.

Une fois que le pipeline a été exécuté il est possible de voir le succès ou nom sur le projet
![Pipeline](https://gitlab.com/jeremie.dequidt/ima_prog_adv/badges/master/pipeline.svg) et le code couvert par les tests ![Coverage](https://gitlab.com/jeremie.dequidt/ima_prog_adv/badges/master/coverage.svg) via les liens [https://gitlab.univ-lille.fr/jeremie.dequidt/ima_prog_adv_ci/badges/master/pipeline.svg](https://gitlab.univ-lille.fr/jeremie.dequidt/ima_prog_adv_ci/badges/master/pipeline.svg) et [https://gitlab.univ-lille.fr/jeremie.dequidt/ima_prog_adv_ci/badges/master/coverage.svg](https://gitlab.univ-lille.fr/jeremie.dequidt/ima_prog_adv_ci/badges/master/coverage.svg)
