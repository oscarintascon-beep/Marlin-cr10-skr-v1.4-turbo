Marlin build helper for CR-10 -> BTT SKR V1.4 Turbo

Contenido del paquete:

Configuration.h
Configuration_adv.h
.github/workflows/build-marlin.yml
README.md
Objetivo:
Este paquete te permite compilar Marlin en GitHub Actions y obtener un firmware.bin listo para flashear a la placa SKR V1.4 Turbo.

Pasos rápidos para usarlo:

Crea un repo nuevo en GitHub e inicialízalo localmente (o sube estos archivos al nuevo repo).
Coloca Configuration.h y Configuration_adv.h en la raíz del repo.
Asegúrate de que el archivo .github/workflows/build-marlin.yml esté en la ruta .github/workflows/.
Haz commit y push a GitHub (branch main o master). GitHub Actions compilará automáticamente.
Abre la pestaña Actions en GitHub, espera a que el job termine y descarga el artefacto firmware.
Notas:

Revisa y ajusta NOZZLE_TO_PROBE_OFFSET tras la primera prueba.
Si la compilación falla por macros, pégame el log y lo corrijo.
Crear la carpeta .github\workflows y el archivo build-marlin.yml
En el Explorador de archivos dentro de C:\Users\otasc\OneDrive\Escritorio\REPOSITORIOGITHUB crea una carpeta llamada .github.
Dentro de .github crea otra carpeta llamada workflows.
Ahora abre Notepad nuevo, pega el contenido siguiente y guarda:
Carpeta: C:\Users\otasc\OneDrive\Escritorio\REPOSITORIOGITHUB.github\workflows
Nombre: build-marlin.yml
Tipo: Todos los archivos (.)
Codificación: UTF-8
Guardar.
Contenido para .github\workflows\build-marlin.yml:
name: Build Marlin for SKR V1.4 Turbo

on:
push:
branches: [ "main", "master" ]
workflow_dispatch:

jobs:
build:
runs-on: ubuntu-latest
steps:
- name: Checkout repo (contains Configuration files)
uses: actions/checkout@v4


  - name: Setup Python      uses: actions/setup-python@v4      with:        python-version: "3.x"  - name: Install PlatformIO      run: |        python -m pip install -U pip        python -m pip install -U platformio  - name: Clone Marlin (bugfix-2.1.x)      run: |        git clone --depth=1 --branch bugfix-2.1.x https://github.com/MarlinFirmware/Marlin.git marlin  - name: Show available envs (debug)      run: |        echo "==== platformio.ini envs ===="        grep -E "^\[env:" -n marlin/platformio.ini || true        echo "============================="  - name: Copy Configuration files into Marlin      run: |        if [ -f ./Configuration.h ] && [ -f ./Configuration_adv.h ]; then          cp -v ./Configuration.h ./Configuration_adv.h marlin/        else          cp -v ./config/Configuration.h ./config/Configuration_adv.h marlin/ || true        fi        ls -l marlin/Configuration.h marlin/Configuration_adv.h || true  - id: detect      name: Detect platformio env for SKR      run: |        env_name=$(grep -E "^\[env:.*(skr|btt|turbo).*" -o marlin/platformio.ini | sed -E "s/^\[env:(.*)\].*/\1/" | head -n1)        if [ -z "$env_name" ]; then          env_name=$(grep -E "^\[env:" -o marlin/platformio.ini | sed -E "s/^\[env:(.*)\].*/\1/" | head -n1)        fi        if [ -z "$env_name" ]; then          echo "No env found in platformio.ini" >&2          exit 1        fi        echo "env_name=$env_name" >> $GITHUB_OUTPUT  - name: Build Marlin with PlatformIO      run: |        echo "Building Marlin for env: ${{ steps.detect.outputs.env_name }}"        python -m platformio run -d marlin -e "${{ steps.detect.outputs.env_name }}" -v  - name: Upload firmware artifact      if: success()      uses: actions/upload-artifact@v4      with:        name: firmware        path: |          marlin/.pio/build/${{ steps.detect.outputs.env_name }}/firmware.bin          marlin/.pio/build/${{ steps.detect.outputs.env_name }}/firmware.hex
