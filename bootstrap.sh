#!/usr/bin/env bash
set -e

echo "== Base system =="
sudo apt update
sudo apt install -y \
  git \
  build-essential \
  clang \
  clangd \
  clang-format \
  tree-sitter-cli \
  gdb \
  valgrind \
  curl

echo "== Neovim =="
if ! command -v nvim >/dev/null 2>&1; then
  sudo snap install nvim --classic
  sudo ln -sf /snap/bin/nvim /usr/local/bin/nvim
fi

echo "== Clone dotfiles (if missing) =="
if [ ! -d "$HOME/dotfiles/.git" ]; then
  git clone https://github.com/ccanning-stack/dotfiles.git "$HOME/dotfiles"
fi

echo "== Link Neovim config =="
mkdir -p "$HOME/.config"

if [ -L "$HOME/.config/nvim" ]; then
  :
elif [ -e "$HOME/.config/nvim" ]; then
  mv "$HOME/.config/nvim" "$HOME/.config/nvim.bak.$(date +%Y%m%d-%H%M%S)"
fi

ln -sfn "$HOME/dotfiles/nvim" "$HOME/.config/nvim"

echo "== Sync Neovim plugins =="
nvim --headless "+Lazy! sync" +qa || true

echo "== Done =="
