let SessionLoad = 1
if &cp | set nocp | endif
let s:so_save = &g:so | let s:siso_save = &g:siso | setg so=0 siso=0 | setl so=-1 siso=-1
let v:this_session=expand("<sfile>:p")
silent only
silent tabonly
cd ~/Work/dungeon-crawl
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
set shortmess=aoO
argglobal
%argdel
set stal=2
tabnew
tabnew
tabnew
tabnew
tabnew
tabnew
tabnew
tabnew
tabnew
tabnew
tabnew
tabnew
tabnew
tabnew
tabnew
tabrewind
edit transform.c
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
set nosplitbelow
set nosplitright
wincmd t
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe '1resize ' . ((&lines * 52 + 31) / 63)
exe 'vert 1resize ' . ((&columns * 81 + 85) / 170)
exe '2resize ' . ((&lines * 52 + 31) / 63)
exe 'vert 2resize ' . ((&columns * 67 + 85) / 170)
argglobal
balt utils.h
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 386 - ((51 * winheight(0) + 26) / 52)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 386
normal! 0
wincmd w
argglobal
if bufexists("transform.h") | buffer transform.h | else | edit transform.h | endif
balt transform_data.h
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 67 - ((51 * winheight(0) + 26) / 52)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 67
normal! 0
wincmd w
exe '1resize ' . ((&lines * 52 + 31) / 63)
exe 'vert 1resize ' . ((&columns * 81 + 85) / 170)
exe '2resize ' . ((&lines * 52 + 31) / 63)
exe 'vert 2resize ' . ((&columns * 67 + 85) / 170)
tabnext
edit game.c
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
set nosplitbelow
set nosplitright
wincmd t
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe '1resize ' . ((&lines * 52 + 31) / 63)
exe 'vert 1resize ' . ((&columns * 81 + 85) / 170)
exe '2resize ' . ((&lines * 52 + 31) / 63)
exe 'vert 2resize ' . ((&columns * 67 + 85) / 170)
argglobal
balt game.h
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 266 - ((51 * winheight(0) + 26) / 52)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 266
normal! 0
wincmd w
argglobal
if bufexists("game.h") | buffer game.h | else | edit game.h | endif
balt utils.h
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 16 - ((15 * winheight(0) + 26) / 52)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 16
normal! 021|
wincmd w
exe '1resize ' . ((&lines * 52 + 31) / 63)
exe 'vert 1resize ' . ((&columns * 81 + 85) / 170)
exe '2resize ' . ((&lines * 52 + 31) / 63)
exe 'vert 2resize ' . ((&columns * 67 + 85) / 170)
tabnext
edit active.c
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
set nosplitbelow
set nosplitright
wincmd t
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe '1resize ' . ((&lines * 52 + 31) / 63)
exe 'vert 1resize ' . ((&columns * 81 + 85) / 170)
exe '2resize ' . ((&lines * 52 + 31) / 63)
exe 'vert 2resize ' . ((&columns * 67 + 85) / 170)
argglobal
balt utils.h
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 42 - ((15 * winheight(0) + 26) / 52)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 42
normal! 0
wincmd w
argglobal
if bufexists("active.h") | buffer active.h | else | edit active.h | endif
balt utils.h
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 57 - ((50 * winheight(0) + 26) / 52)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 57
normal! 0
wincmd w
exe '1resize ' . ((&lines * 52 + 31) / 63)
exe 'vert 1resize ' . ((&columns * 81 + 85) / 170)
exe '2resize ' . ((&lines * 52 + 31) / 63)
exe 'vert 2resize ' . ((&columns * 67 + 85) / 170)
tabnext
edit map.c
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
set nosplitbelow
set nosplitright
wincmd t
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe '1resize ' . ((&lines * 52 + 31) / 63)
exe 'vert 1resize ' . ((&columns * 81 + 85) / 170)
exe '2resize ' . ((&lines * 52 + 31) / 63)
exe 'vert 2resize ' . ((&columns * 67 + 85) / 170)
argglobal
balt utils.h
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 73 - ((36 * winheight(0) + 26) / 52)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 73
normal! 0
wincmd w
argglobal
if bufexists("map.h") | buffer map.h | else | edit map.h | endif
balt map.c
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 42 - ((41 * winheight(0) + 26) / 52)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 42
normal! 0
wincmd w
exe '1resize ' . ((&lines * 52 + 31) / 63)
exe 'vert 1resize ' . ((&columns * 81 + 85) / 170)
exe '2resize ' . ((&lines * 52 + 31) / 63)
exe 'vert 2resize ' . ((&columns * 67 + 85) / 170)
tabnext
edit item.c
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
set nosplitbelow
set nosplitright
wincmd t
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe '1resize ' . ((&lines * 52 + 31) / 63)
exe 'vert 1resize ' . ((&columns * 81 + 85) / 170)
exe '2resize ' . ((&lines * 52 + 31) / 63)
exe 'vert 2resize ' . ((&columns * 67 + 85) / 170)
argglobal
balt utils.h
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 107 - ((51 * winheight(0) + 26) / 52)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 107
normal! 0
wincmd w
argglobal
if bufexists("item.h") | buffer item.h | else | edit item.h | endif
balt item.c
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 1 - ((0 * winheight(0) + 26) / 52)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 1
normal! 0
wincmd w
exe '1resize ' . ((&lines * 52 + 31) / 63)
exe 'vert 1resize ' . ((&columns * 81 + 85) / 170)
exe '2resize ' . ((&lines * 52 + 31) / 63)
exe 'vert 2resize ' . ((&columns * 67 + 85) / 170)
tabnext
edit creature.c
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
set nosplitbelow
set nosplitright
wincmd t
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe '1resize ' . ((&lines * 52 + 31) / 63)
exe 'vert 1resize ' . ((&columns * 74 + 85) / 170)
exe '2resize ' . ((&lines * 52 + 31) / 63)
exe 'vert 2resize ' . ((&columns * 74 + 85) / 170)
argglobal
balt \'
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 524 - ((35 * winheight(0) + 26) / 52)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 524
normal! 041|
wincmd w
argglobal
if bufexists("creature.h") | buffer creature.h | else | edit creature.h | endif
balt creature.c
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 63 - ((36 * winheight(0) + 26) / 52)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 63
normal! 019|
wincmd w
exe '1resize ' . ((&lines * 52 + 31) / 63)
exe 'vert 1resize ' . ((&columns * 74 + 85) / 170)
exe '2resize ' . ((&lines * 52 + 31) / 63)
exe 'vert 2resize ' . ((&columns * 74 + 85) / 170)
tabnext
edit /usr/include/SDL2/SDL_render.h
set splitbelow splitright
set nosplitbelow
set nosplitright
wincmd t
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
argglobal
balt /usr/include/SDL2
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 875 - ((15 * winheight(0) + 26) / 53)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 875
normal! 03|
lcd ~/Work/dungeon-crawl
tabnext
edit ~/Work/dungeon-crawl/memory.c
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
set nosplitbelow
set nosplitright
wincmd t
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe '1resize ' . ((&lines * 52 + 31) / 63)
exe 'vert 1resize ' . ((&columns * 77 + 85) / 170)
exe '2resize ' . ((&lines * 52 + 31) / 63)
exe 'vert 2resize ' . ((&columns * 71 + 85) / 170)
argglobal
balt ~/Work/dungeon-crawl/utils.h
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 137 - ((51 * winheight(0) + 26) / 52)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 137
normal! 0
wincmd w
argglobal
if bufexists("~/Work/dungeon-crawl/memory.h") | buffer ~/Work/dungeon-crawl/memory.h | else | edit ~/Work/dungeon-crawl/memory.h | endif
balt ~/Work/dungeon-crawl/memory.c
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 69 - ((50 * winheight(0) + 26) / 52)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 69
normal! 0
wincmd w
exe '1resize ' . ((&lines * 52 + 31) / 63)
exe 'vert 1resize ' . ((&columns * 77 + 85) / 170)
exe '2resize ' . ((&lines * 52 + 31) / 63)
exe 'vert 2resize ' . ((&columns * 71 + 85) / 170)
tabnext
edit ~/Work/dungeon-crawl/input.c
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
set nosplitbelow
set nosplitright
wincmd t
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe 'vert 1resize ' . ((&columns * 81 + 85) / 170)
exe 'vert 2resize ' . ((&columns * 88 + 85) / 170)
argglobal
balt ~/Work/dungeon-crawl/input.h
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 21 - ((20 * winheight(0) + 30) / 60)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 21
normal! 0
wincmd w
argglobal
if bufexists("~/Work/dungeon-crawl/input.h") | buffer ~/Work/dungeon-crawl/input.h | else | edit ~/Work/dungeon-crawl/input.h | endif
balt ~/Work/dungeon-crawl/input.c
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 48 - ((47 * winheight(0) + 30) / 60)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 48
normal! 05|
wincmd w
exe 'vert 1resize ' . ((&columns * 81 + 85) / 170)
exe 'vert 2resize ' . ((&columns * 88 + 85) / 170)
tabnext
edit ~/Work/dungeon-crawl/graphics.c
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
set nosplitbelow
set nosplitright
wincmd t
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe '1resize ' . ((&lines * 52 + 31) / 63)
exe 'vert 1resize ' . ((&columns * 81 + 85) / 170)
exe '2resize ' . ((&lines * 52 + 31) / 63)
exe 'vert 2resize ' . ((&columns * 67 + 85) / 170)
argglobal
balt ~/Work/dungeon-crawl/utils.h
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 410 - ((51 * winheight(0) + 26) / 52)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 410
normal! 0
wincmd w
argglobal
if bufexists("~/Work/dungeon-crawl/graphics.h") | buffer ~/Work/dungeon-crawl/graphics.h | else | edit ~/Work/dungeon-crawl/graphics.h | endif
balt ~/Work/dungeon-crawl/utils.h
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 72 - ((28 * winheight(0) + 26) / 52)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 72
normal! 018|
wincmd w
exe '1resize ' . ((&lines * 52 + 31) / 63)
exe 'vert 1resize ' . ((&columns * 81 + 85) / 170)
exe '2resize ' . ((&lines * 52 + 31) / 63)
exe 'vert 2resize ' . ((&columns * 67 + 85) / 170)
tabnext
edit ~/Work/dungeon-crawl/kiss_sdl/kiss_general.c
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
set nosplitbelow
set nosplitright
wincmd t
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe '1resize ' . ((&lines * 52 + 31) / 63)
exe 'vert 1resize ' . ((&columns * 80 + 85) / 170)
exe '2resize ' . ((&lines * 52 + 31) / 63)
exe 'vert 2resize ' . ((&columns * 68 + 85) / 170)
argglobal
balt ~/Work/dungeon-crawl/kiss_sdl/kiss_sdl.h
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 248 - ((51 * winheight(0) + 26) / 52)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 248
normal! 0
wincmd w
argglobal
if bufexists("~/Work/dungeon-crawl/kiss_sdl/kiss_sdl.h") | buffer ~/Work/dungeon-crawl/kiss_sdl/kiss_sdl.h | else | edit ~/Work/dungeon-crawl/kiss_sdl/kiss_sdl.h | endif
balt ~/Work/dungeon-crawl/kiss_sdl/kiss_general.c
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 314 - ((30 * winheight(0) + 26) / 52)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 314
normal! 010|
wincmd w
exe '1resize ' . ((&lines * 52 + 31) / 63)
exe 'vert 1resize ' . ((&columns * 80 + 85) / 170)
exe '2resize ' . ((&lines * 52 + 31) / 63)
exe 'vert 2resize ' . ((&columns * 68 + 85) / 170)
tabnext
edit ~/Work/dungeon-crawl/ui.c
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
set nosplitbelow
set nosplitright
wincmd t
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe '1resize ' . ((&lines * 52 + 31) / 63)
exe 'vert 1resize ' . ((&columns * 81 + 85) / 170)
exe '2resize ' . ((&lines * 52 + 31) / 63)
exe 'vert 2resize ' . ((&columns * 67 + 85) / 170)
argglobal
balt ~/Work/dungeon-crawl/ui.h
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 163 - ((51 * winheight(0) + 26) / 52)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 163
normal! 0
wincmd w
argglobal
if bufexists("~/Work/dungeon-crawl/ui.h") | buffer ~/Work/dungeon-crawl/ui.h | else | edit ~/Work/dungeon-crawl/ui.h | endif
balt ~/Work/dungeon-crawl/ui.c
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 21 - ((20 * winheight(0) + 26) / 52)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 21
normal! 026|
wincmd w
exe '1resize ' . ((&lines * 52 + 31) / 63)
exe 'vert 1resize ' . ((&columns * 81 + 85) / 170)
exe '2resize ' . ((&lines * 52 + 31) / 63)
exe 'vert 2resize ' . ((&columns * 67 + 85) / 170)
tabnext
edit ~/Work/dungeon-crawl/utils.c
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
set nosplitbelow
set nosplitright
wincmd t
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe '1resize ' . ((&lines * 52 + 31) / 63)
exe 'vert 1resize ' . ((&columns * 77 + 85) / 170)
exe '2resize ' . ((&lines * 52 + 31) / 63)
exe 'vert 2resize ' . ((&columns * 71 + 85) / 170)
argglobal
balt ~/Work/dungeon-crawl/utils.h
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 97 - ((49 * winheight(0) + 26) / 52)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 97
normal! 0
wincmd w
argglobal
if bufexists("~/Work/dungeon-crawl/utils.h") | buffer ~/Work/dungeon-crawl/utils.h | else | edit ~/Work/dungeon-crawl/utils.h | endif
balt ~/Work/dungeon-crawl/utils.c
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 25 - ((24 * winheight(0) + 26) / 52)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 25
normal! 06|
wincmd w
exe '1resize ' . ((&lines * 52 + 31) / 63)
exe 'vert 1resize ' . ((&columns * 77 + 85) / 170)
exe '2resize ' . ((&lines * 52 + 31) / 63)
exe 'vert 2resize ' . ((&columns * 71 + 85) / 170)
tabnext
edit ~/Work/dungeon-crawl/vector.c
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
set nosplitbelow
set nosplitright
wincmd t
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe '1resize ' . ((&lines * 52 + 31) / 63)
exe 'vert 1resize ' . ((&columns * 81 + 85) / 170)
exe '2resize ' . ((&lines * 52 + 31) / 63)
exe 'vert 2resize ' . ((&columns * 67 + 85) / 170)
argglobal
balt ~/Work/dungeon-crawl/vector.h
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 26 - ((15 * winheight(0) + 26) / 52)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 26
normal! 0
wincmd w
argglobal
if bufexists("~/Work/dungeon-crawl/vector.h") | buffer ~/Work/dungeon-crawl/vector.h | else | edit ~/Work/dungeon-crawl/vector.h | endif
balt ~/Work/dungeon-crawl/vector.c
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 79 - ((43 * winheight(0) + 26) / 52)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 79
normal! 0
wincmd w
exe '1resize ' . ((&lines * 52 + 31) / 63)
exe 'vert 1resize ' . ((&columns * 81 + 85) / 170)
exe '2resize ' . ((&lines * 52 + 31) / 63)
exe 'vert 2resize ' . ((&columns * 67 + 85) / 170)
tabnext
edit ~/Work/dungeon-crawl/tests.c
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
set nosplitbelow
set nosplitright
wincmd t
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe '1resize ' . ((&lines * 52 + 31) / 63)
exe 'vert 1resize ' . ((&columns * 81 + 85) / 170)
exe '2resize ' . ((&lines * 52 + 31) / 63)
exe 'vert 2resize ' . ((&columns * 67 + 85) / 170)
argglobal
balt ~/Work/dungeon-crawl/tests.h
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 105 - ((51 * winheight(0) + 26) / 52)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 105
normal! 0
wincmd w
argglobal
if bufexists("~/Work/dungeon-crawl/tests.h") | buffer ~/Work/dungeon-crawl/tests.h | else | edit ~/Work/dungeon-crawl/tests.h | endif
balt ~/Work/dungeon-crawl/tests.c
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 21 - ((20 * winheight(0) + 26) / 52)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 21
normal! 04|
wincmd w
exe '1resize ' . ((&lines * 52 + 31) / 63)
exe 'vert 1resize ' . ((&columns * 81 + 85) / 170)
exe '2resize ' . ((&lines * 52 + 31) / 63)
exe 'vert 2resize ' . ((&columns * 67 + 85) / 170)
tabnext
edit ~/Work/dungeon-crawl/build.sh
set splitbelow splitright
set nosplitbelow
set nosplitright
wincmd t
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
argglobal
balt ~/Work/dungeon-crawl/vector.c
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 1 - ((0 * winheight(0) + 26) / 53)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 1
normal! 09|
tabnext 9
set stal=1
badd +1 ~/Work/dungeon-crawl/transform.c
badd +1 ~/Work/dungeon-crawl/game.c
badd +1 ~/Work/dungeon-crawl/active.c
badd +1 ~/Work/dungeon-crawl/map.c
badd +1 ~/Work/dungeon-crawl/item.c
badd +1 ~/Work/dungeon-crawl/creature.c
badd +1 /usr/include/SDL2/SDL_render.h
badd +13 ~/Work/dungeon-crawl/memory.c
badd +13 ~/Work/dungeon-crawl/input.c
badd +1 ~/Work/dungeon-crawl/graphics.c
badd +106 ~/Work/dungeon-crawl/kiss_sdl/kiss_general.c
badd +1 ~/Work/dungeon-crawl/ui.c
badd +20 ~/Work/dungeon-crawl/utils.c
badd +1 ~/Work/dungeon-crawl/vector.c
badd +1 ~/Work/dungeon-crawl/tests.c
badd +1 ~/Work/dungeon-crawl/build.sh
badd +25 ~/Work/dungeon-crawl/utils.h
badd +35 ~/Work/dungeon-crawl/transform.h
badd +1 ~/Work/dungeon-crawl/transform_data.h
badd +1 ~/Work/dungeon-crawl/game.h
badd +45 ~/Work/dungeon-crawl/active.h
badd +42 ~/Work/dungeon-crawl/map.h
badd +41 ~/Work/dungeon-crawl/item.h
badd +19 ~/Work/dungeon-crawl/\'
badd +59 ~/Work/dungeon-crawl/creature.h
badd +1 /usr/include/SDL2
badd +20 ~/Work/dungeon-crawl/memory.h
badd +42 ~/Work/dungeon-crawl/input.h
badd +40 ~/Work/dungeon-crawl/graphics.h
badd +87 ~/Work/dungeon-crawl/kiss_sdl/kiss_sdl.h
badd +13 ~/Work/dungeon-crawl/ui.h
badd +1 ~/Work/dungeon-crawl/vector.h
badd +1 ~/Work/dungeon-crawl/tests.h
badd +13 ~/Work/dungeon-crawl/transform_data.c
badd +1 ~/.vimrc
badd +172 ~/Work/dungeon-crawl/text.c
badd +62 ~/Work/Assembly/game4x/c_source/main.c
badd +1 ~/Work/Assembly/game4x/asm_source/build_asm.sh
badd +1 ~/Work/Assembly/game4x/c_source/utils.c
badd +95 ~/Work/Assembly/game4x/c_source/gl_game.c
badd +1 ~/Work/Assembly/game4x/c_source/texture.c
badd +406 ~/Work/Assembly/game4x/c_source/text.c
badd +82 ~/Work/Assembly/game4x/c_source/input.c
badd +11 ~/Work/dungeon-crawl/text.h
badd +1 ~/Work/Assembly/game4x/asm_source
badd +1 ~/Work/Assembly/game4x/c_source
badd +1 ~/Work/Assembly/game4x/c_source/game.c
badd +1 ~/Work/dungeon-crawl/\[Vundle]\ Installer
badd +1 ~./vimrc
badd +1 ~/Work/dungeon-crawl/game.H
badd +227 ~/Work/dungeon-crawl/exe
badd +681 ~/Work/dungeon-crawl/Session.vim
badd +17 ~/Work/dungeon-crawl/\\
badd +14 ~/Work/dungeon-crawl/shader.frag
badd +11 ~/Work/dungeon-crawl/shader.vert
badd +1 ~/Work/dungeon-crawl/memoryc.
badd +59 /usr/include/SDL2/SDL.h
badd +1 ~/Work/dungeon-crawl
badd +45 ~/Work/dungeon-crawl/kiss_sdl/kiss_LICENSE
badd +46 ~/Work/dungeon-crawl/kiss_sdl/kiss_draw.c
badd +27 ~/Work/dungeon-crawl/kiss_sdl/kiss_example1.c
badd +64 ~/Work/dungeon-crawl/kiss_sdl/kiss_example2.c
badd +1321 ~/Work/dungeon-crawl/kiss_sdl/kiss_font.ttf
badd +271 ~/Work/dungeon-crawl/kiss_sdl/kiss_widgets.c
if exists('s:wipebuf') && len(win_findbuf(s:wipebuf)) == 0
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20 shortmess=filnxtToOSc
set winminheight=1 winminwidth=1
let s:sx = expand("<sfile>:p:r")."x.vim"
if filereadable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &g:so = s:so_save | let &g:siso = s:siso_save
let g:this_session = v:this_session
let g:this_obsession = v:this_session
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
