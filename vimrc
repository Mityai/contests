set nocompatible
filetype off

set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()
Plugin 'gmarik/Vundle.vim'
Plugin 'tpope/vim-fugitive'
Plugin 'L9'
Plugin 'git://git.wincent.com/command-t.git'
Plugin 'rstacruz/sparkup', {'rtp': 'vim/'}
Plugin 'user/L9', {'name': 'newL9'}

Plugin 'scrooloose/nerdtree'
Plugin 'tpope/vim-repeat'
"Plugin 'vim-airline/vim-airline'
"Plugin 'vim-airline/vim-airline-themes'
Plugin 'itchyny/lightline.vim'
Plugin 'edkolev/tmuxline.vim'
"Plugin 'rdnetto/YCM-Generator', { 'branch': 'stable'}
Plugin 'Igorjan94/codeforces.vim'
Plugin 'wakatime/vim-wakatime'
call vundle#end()
filetype plugin indent on

syntax enable
"highlight Normal ctermfg=grey ctermbg=darkblue
"set background=dark
"let g:solarized_termcolors=256
"let g:solarized_visibility = "high"
"let g:solarized_contrast = "high"
"let g:solarized_termtrans=1
"colorscheme grb4
"colorscheme eclipse
"color solarized
set term=xterm-256color
set t_Co=256
colorscheme wombat256mod

set backspace=indent,eol,start

set number
"set rnu

set smartindent

set tabstop=4
set expandtab
set shiftwidth=4

highlight OverLength ctermbg=red ctermfg=white guibg=#592929
match OverLength /\%101v.\+/

"set list
"set listchars=trail:.

set mouse=a
set ttymouse=xterm2
set mousehide
set showmatch
set autoread

"set statusline=%F%m%r%h%w\ [%{&fileencoding}]\ %y\ [ASCII=\%03.3b]\ [%02l:%02v]\ [%l/%L]
set laststatus=2

set noruler
set title
set whichwrap=b,<,>,[,],l,h
set virtualedit=all
set autoread
set clipboard=unnamed
set linebreak
set dy=lastline
set hls
set iminsert=0
set imsearch=0

set noerrorbells 
set novisualbell

set noshowmode
"set ambiwidth=double

set nobackup
set noswapfile

hi StatusLine gui=reverse cterm=reverse
hi LineNr ctermfg=237
au BufNewFile,BufRead *.cpp set syntax=cpp11

nnoremap <Left> :tabprevious<CR>
nnoremap <Right> :tabnext<CR>

nnoremap <Down> :tabclose<CR>
nnoremap <Up> :tab sp 

map <F2> :NERDTreeToggle<CR>
"map <F12> :YcmCompleter GoTo<CR>

" clang++
:map <F5> :w<cr> :!clang++ -g -std=c++1z -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -O2 -Wall -Wextra -Wshadow -Wunused -Wfloat-equal -Wconversion -fsanitize=address,undefined % -o %< <cr>
:map <F9> :w<cr> :!clang++ -g -std=c++1z -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -O2 -Wall -Wextra -Wshadow -Wunused -Wfloat-equal -Wconversion -fsanitize=address,undefined % -o %< && ./%< <cr>
:map <F11> :w<cr> :!clang++ -std=c++14 -O2 % -o %< && time ./%< <cr>

" gcc
:map <S-F12> :w<cr> :!gcc -O2 -Wall -Werror -std=gnu11 -lm % -o %< <cr>
:map <F12> :w<cr> :!gcc -O2 -Wall -Werror -std=gnu11 -lm % -o %< && time ./%< <cr>

" run executable
:map <F10> :!./%< <cr>

" python3
:map \;; :w <cr>:!python3 % <cr>

" latex
:map \ll :w <cr>:!xelatex --shell-escape main.tex && open -a "Safari" main.pdf <cr>
":map \ll :w <cr>:!pdflatex main.tex && open main.pdf <cr>

set encoding=utf-8
scriptencoding utf-8
set fileencodings=utf8,cp1281

map <F4> :cn<Cr>zvzz:cc<Cr> "следующая ошибка 
map <S-F4> :cp<Cr>zvzz:cc<Cr> "предедущая ошибка

let g:Powerline_symbols = 'fancy'
"let g:clang_library_path='/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/libclang.dylib'
"let g:lightline = {
 "     \ 'colorscheme': 'wombat',
 "     \ 'component': {
 "     \   'readonly': '%{&filetype=="help"?"":&readonly?"⭤":""}',
 "     \   'modified': '%{&filetype=="help"?"":&modified?"+":&modifiable?"":"-"}'
 "     \ },
 "     \ 'component_visible_condition': {
 "     \   'readonly': '(&filetype!="help"&& &readonly)',
 "     \   'modified': '(&filetype!="help"&&(&modified||!&modifiable))'
 "     \ },
 "     \ 'separator': { 'left': "\u2b80", 'right': "\u2b82" },
 "     \ 'subseparator': { 'left': "\u2b81", 'right': "\u2b83" }
 "     \ }
let g:lightline = {
      \ 'colorscheme': 'wombat',
      \ 'active': {
      \   'left': [ [ 'mode', 'paste' ],
      \             [ 'fugitive', 'filename' ] ]
      \ },
      \ 'component_function': {
      \   'fugitive': 'LightLineFugitive',
      \   'readonly': 'LightLineReadonly',
      \   'modified': 'LightLineModified',
      \   'filename': 'LightLineFilename'
      \ },
      \ 'separator': { 'left': '⮀', 'right': '⮂' },
      \ 'subseparator': { 'left': '⮁', 'right': '⮃' }
      \ }

function! LightLineModified()
  if &filetype == "help"
    return ""
  elseif &modified
    return "+"
  elseif &modifiable
    return ""
  else
    return ""
  endif
endfunction

function! LightLineReadonly()
  if &filetype == "help"
    return ""
  elseif &readonly
    return "⭤"
  else
    return ""
  endif
endfunction

function! LightLineFugitive()
  return exists('*fugitive#head') ? fugitive#head() : ''
endfunction

function! LightLineFilename()
  return ('' != LightLineReadonly() ? LightLineReadonly() . ' ' : '') .
       \ ('' != expand('%t') ? expand('%:p:h') . '/' . expand('%t') : '[No Name]') .
       \ ('' != LightLineModified() ? ' ' . LightLineModified() : '')
endfunction

function! LightLineFugitive()
  if exists("*fugitive#head")
    let branch = fugitive#head()
    return branch !=# '' ? '⭠ '.branch : ''
  endif
  return ''
endfunction
"let g:airline_powerline_fonts = 1
"let g:airline#extensions#tabline#enabled = 1
