#!/bin/bash

mkdir artifacts
cd $1
find . -name *.deb -exec cp {} ../artifacts \;
find . -name *.rpm -exec cp {} ../artifacts \;
find . -name *.sh -exec cp {} ../artifacts \;
find . -name *.tar.bz2 -exec cp {} ../artifacts \;
find . -name *.tar.gz -exec cp {} ../artifacts \;
find . -name *.tar.Z -exec cp {} ../artifacts \;
find . -name *.zip -exec cp {} ../artifacts \;
cp install_manifest.txt ../artifacts/

echo "rm -rf $(cat install_manifest.txt)" > ../artifacts/uninstall.sh
chmod +x ../artifacts/uninstall.sh

cd ..
