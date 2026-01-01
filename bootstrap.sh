#!/usr/bin/env bash
set -e

echo "== Base system =="
sudo apt update
sudo apt install -y \
  git \
  build-essential \
  clang \
  tree-sitter-cli \
  curl

echo "== Neovim =="
if ! command -v nvim >/dev/null; then
  sudo snap install nvim --classic
  sudo ln -sf /snap/bin/nvim /usr/local/bin/nvim
fi

echo "== Clone Neovim config =="
if [ ! -d "$HOME/.config/nvim" ]; then
  git clone git@github.com:ccanning-stack/nvim-config.git ~/.config/nvim
fi

echo "== Done =="
echo "Open nvim and run :Lazy sync"
