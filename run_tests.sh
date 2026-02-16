#!/bin/bash

# Couleurs pour faire joli dans le terminal
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

echo "🛠️  Compilation en cours..."
make > /dev/null

echo "🧪 Lancement des tests..."
# On donne input.txt à ton programme et on sauvegarde le résultat dans actual.txt
./computorv2 < tests/input.txt > tests/actual.txt

# On compare le résultat obtenu avec le résultat attendu
diff -u tests/expected.txt tests/actual.txt > tests/diff.log

# Si diff ne trouve aucune différence, il renvoie 0
if [ $? -eq 0 ]; then
    echo -e "${GREEN}✅ TOUS LES TESTS PASSENT !${NC}"
    rm tests/actual.txt tests/diff.log
else
    echo -e "${RED}❌ ERREUR TROUVÉE !${NC}"
    echo "Regarde les différences ci-dessous :"
    cat tests/diff.log
fi