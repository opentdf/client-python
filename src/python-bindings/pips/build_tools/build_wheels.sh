set -e
set -x


python -m pip install cibuildwheel==2.14.1
python -m cibuildwheel --output-dir wheelhouse