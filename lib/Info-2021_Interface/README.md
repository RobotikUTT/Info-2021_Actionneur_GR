# Description de l'interface

Ce repo contient les informations utilisées pour la communication entre composants sur le bus CAN.

## Dossier can_description
Contient les fichiers JSON de description cross-language

## Dossier cpp\_header\_gen
Contient le script (Python3) de génération des headers pour C++.
### Générer le fichier header
Lancer le script Python3:
```sh
./generate_header.py
```

## Dossier python_parser
Module Python3 pour parser les fichiers de description JSON.

___

La documentation est disponible dans `python_parser/doc/`.\
Elle peut aussi être générée à l'aide de pdoc3 (`pip install pdoc3`) avec:
```sh
pdoc --html -o python_parser/doc/ python_parser/ --force
```

Globalement, ce module met à disposition 3 listes:
* _devicesList_ - Liste d'objets Device
* _messagesList_ - Liste d'objets Message
* _framesList_ - Liste d'objets Frame
