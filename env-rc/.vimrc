noremap! <C-?> <C-h>
"colorscheme desert
colorscheme ron
set clipboard=unnamedplus
"mouse in normal mode
set mouse=n
set updatetime=1000
set ruler		" show the cursor position all the time
set statusline=[%F]%y%r%m%*%=[Line:%l/%L,Column:%c][%p%%]
set laststatus=2
filetype plugin indent on
" show existing tab with 4 spaces width
set tabstop=4
" when indenting with '>', use 4 spaces width
set shiftwidth=4
" On pressing tab, insert 4 spaces
"set expandtab
set autoindent
set nu
set nobackup
set noswapfile
"Search settings
set hlsearch
set incsearch
set ignorecase
"Use za zo to fold code
set foldmethod=syntax
set foldlevelstart=99
"Taglist settings
let Tlist_Show_One_File=1
let Tlist_Auto_Open=0
let Tlist_Exit_OnlyWindow=1
let Tlist_Process_File_Always=1
let Tlist_WinWidth = 50
map <silent> <F6> :TlistToggle<cr>

"Setup cscope or gtags(first)
if executable("gtags") && filereadable("GTAGS")
    let tag_prg="gtags-cscope"
    let tag_db="GTAGS"
elseif executable("cscope") && filereadable("cscope.out")
    let tag_prg="cscope"
    let tag_db="cscope.out"
endif
if exists("tag_prg") && exists("tag_db")
    execute "set csprg=".tag_prg
    set csto=0
    set cst
    set cscopequickfix=s-,c-,d-,i-,t-,e-
    set nocsverb
    execute "cs add ".tag_db
    set csverb
    nmap <C-\>s :cs find s <C-R>=expand("<cword>")<CR><CR> :copen<CR><CR>
    nmap <C-\>g :cs find g <C-R>=expand("<cword>")<CR><CR>
    nmap <C-\>d :cs find d <C-R>=expand("<cword>")<CR><CR> :copen<CR><CR>
    nmap <C-\>c :cs find c <C-R>=expand("<cword>")<CR><CR> :copen<CR><CR>
    nmap <C-\>t :cs find t <C-R>=expand("<cword>")<CR><CR> :copen<CR><CR>
    nmap <C-\>e :cs find e <C-R>=expand("<cword>")<CR><CR> :copen<CR><CR>
    nmap <C-\>f :cs find f <C-R>=expand("<cfile>")<CR><CR>
    nmap <C-\>i :cs find i <C-R>=expand("<cfile>")<CR><CR> :copen<CR><CR>
endif

" Use zz to exit Insert mode (instead of having to type Escape key which is
" far away on the keyboard. To really type 'zz', you have to wait a small
" timeout in between both characters.
inoremap zz <Esc>

"don't overwrite last copy
vnoremap p "0p
vnoremap P "0P
vnoremap y "0y
vnoremap d "0d

"auto format
noremap <F3> :Autoformat<CR><CR>

"MRU
let MRU_File=$PWD . '/.vim_mru_files'

" Uncomment the following to have Vim jump to the last position when
" reopening a file
if has("autocmd")
  au BufReadPost * if line("'\"") > 1 && line("'\"") <= line("$") | exe "normal! g'\"" | endif
endif

"show space in end of line
highlight WhitespaceEOL ctermbg=red guibg=red
match WhitespaceEOL /\s\+$/
