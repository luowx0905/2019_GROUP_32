__AUTHOR__="Ewan Drever-Smith"
set -e

mkdir code_docs
cd code_docs

# Use the Token to gain access to the private repo.
git clone -b gh-pages "https://${GH_REPO_TOKEN}@${GH_REPO_REF}"
cd $GH_REPO_NAME

echo $PWD #these lines were used for debugging travis
echo $DOXYFILE

git config --global push.default simple
git config user.name "Travis CI"
git config user.email "travis@travis-ci.com"

rm -rf *
echo "" > .nojekyll #Creates a file called .nojekyll so that jekyll is not used on this gh-page
doxygen $DOXYFILE 2>&1 | tee doxygen.log #runs doxygen and outputs stdout and stderr to doxygen.log
if [ -d "html" ] && [ -f "html/index.html" ]; then
  mv html/* ./ #moves everything inside html into the root directory so can be accessed from https://edrever-smith.github.io/2019_GROUP_32/
  git add --all
  git commit -m "Deploy docs: ${TRAVIS_BUILD_NUMBER}" -m "Commit: ${TRAVIS_COMMIT}"
  git push --force "https://${GH_REPO_TOKEN}@${GH_REPO_REF}" > /dev/null 2>&1
else
  echo '' >&2
  echo 'Warning: No documentation (html) files have been found!' >&2
  echo 'Warning: Not going to push the documentation to GitHub!' >&2
  exit 1
fi
