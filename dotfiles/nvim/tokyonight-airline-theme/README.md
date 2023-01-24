# TokyoNight para o Vim-Airline

Infelizmente o tema TokyoNight não tem suporte oficial para o vim-airline. Sendo assim, um workaround que encontrei na internet foi copiar a configuração do vim-airline para o Vim (e não o NeoVim, editor que tenho usado atualmente) e colar essa configuração na pasta relativa aos temas do vim-airline no NeoVim.

Sendo assim, basta copiar o arquivo ```tokyonight.vim``` para o diretório ```$HOME/.local/share/nvim/site/autoload/airline/themes```. Isso, junto das configurações já presentes nos dotfiles do NeoVim, deve ser o suficiente para o tema ser habilitado corretamente.