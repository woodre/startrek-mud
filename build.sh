#!/usr/bin/env bash
# =============================================================
# Star Trek: Infinite Horizons - LDMud Build Script
# =============================================================
set -e

GAME_DIR="$(cd "$(dirname "$0")" && pwd)"
LIB_DIR="$GAME_DIR/lib"
BIN_DIR="$GAME_DIR/bin"
LOG_DIR="$LIB_DIR/log"
SAVE_DIR="$LIB_DIR/secure/players"
LDMUD_SRC="$GAME_DIR/ldmud_src"

echo "=== Star Trek: Infinite Horizons Setup ==="

# 1. Install build dependencies
echo "[1/6] Installing dependencies..."
sudo apt-get update -qq
sudo apt-get install -y build-essential autoconf pkg-config bison \
    libpcre3-dev libssl-dev git telnet

# 2. Clone LDMud (latest stable branch)
if [ ! -d "$LDMUD_SRC" ]; then
    echo "[2/6] Cloning LDMud source..."
    git clone --depth=1 --branch master https://github.com/ldmud/ldmud.git "$LDMUD_SRC"
else
    echo "[2/6] LDMud source exists, updating..."
    cd "$LDMUD_SRC" && git pull && cd "$GAME_DIR"
fi

# 3. Build LDMud
echo "[3/6] Building LDMud driver..."
mkdir -p "$BIN_DIR"
# autogen.sh must run before configure - it generates the configure script
cd "$LDMUD_SRC/src"
echo "    Running autogen.sh..."
./autogen.sh
./configure --prefix="$GAME_DIR" \
    --enable-use-pcre \
    --enable-use-tls=no \
    --disable-use-mccp
make -j$(nproc)
cp ldmud "$BIN_DIR/ldmud"
echo "    LDMud binary: $BIN_DIR/ldmud"

# 4. Create runtime directories
echo "[4/6] Creating runtime directories..."
mkdir -p "$LOG_DIR"
mkdir -p "$SAVE_DIR"
touch "$LOG_DIR/.gitkeep"
touch "$SAVE_DIR/.gitkeep"

# 5. Write startup script
echo "[5/6] Writing startup script..."
cat > "$GAME_DIR/start.sh" << 'STARTSCRIPT'
#!/usr/bin/env bash
GAME_DIR="$(cd "$(dirname "$0")" && pwd)"
echo "Starting Star Trek: Infinite Horizons on port 4242..."
exec "$GAME_DIR/bin/ldmud" \
    --master "$GAME_DIR/lib/secure/master" \
    --mudlib "$GAME_DIR/lib" \
    --debug-file "$GAME_DIR/lib/log/debug.log" \
    --hard-malloc-limit 0 \
    4242
STARTSCRIPT
chmod +x "$GAME_DIR/start.sh"

echo "[6/6] Done!"
echo ""
echo "To start the MUD:   ./start.sh"
echo "To connect:         telnet localhost 4242"
echo ""
echo "Live long and prosper."
