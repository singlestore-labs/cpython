set -exuo pipefail

rc --reindex
git grep "($1)" | sed "s/.*($1)[ {]*\([a-zA-Z1-9_]\+\).*/\1/" > functions.txt
cat functions.txt | xargs -I % rc -F % > decls.txt
cat decls.txt | grep -v "," > bad_decls
cat bad_decls | sed 's/ *\(.*\):.*:.*:\s*\(.*\)).*/sed -i '\''s.\2).\2, void *Py_UNUSED(ignored)).'\'' \1/' | sed s/\*/\\\\*/ >  replacements
# chmod +x ./replacements
# ./replacements
