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
exe 'vert 1resize ' . ((&columns * 117 + 91) / 182)
exe 'vert 2resize ' . ((&columns * 64 + 91) / 182)
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
let s:l = 165 - ((24 * winheight(0) + 26) / 52)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 165
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
let s:l = 32 - ((31 * winheight(0) + 26) / 52)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 32
normal! 09|
wincmd w
exe 'vert 1resize ' . ((&columns * 117 + 91) / 182)
exe 'vert 2resize ' . ((&columns * 64 + 91) / 182)
tabnext
edit animation.c
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
exe 'vert 1resize ' . ((&columns * 87 + 91) / 182)
exe 'vert 2resize ' . ((&columns * 94 + 91) / 182)
argglobal
balt animation.h
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 51 - ((21 * winheight(0) + 26) / 52)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 51
normal! 024|
wincmd w
argglobal
if bufexists("animation.h") | buffer animation.h | else | edit animation.h | endif
balt animation.c
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 19 - ((18 * winheight(0) + 26) / 52)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 19
normal! 0
wincmd w
exe 'vert 1resize ' . ((&columns * 87 + 91) / 182)
exe 'vert 2resize ' . ((&columns * 94 + 91) / 182)
tabnext
edit temporary_animation.c
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
exe 'vert 1resize ' . ((&columns * 87 + 91) / 182)
exe 'vert 2resize ' . ((&columns * 94 + 91) / 182)
argglobal
balt temporary_animation.h
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 88 - ((50 * winheight(0) + 26) / 52)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 88
normal! 0
wincmd w
argglobal
if bufexists("temporary_animation.h") | buffer temporary_animation.h | else | edit temporary_animation.h | endif
balt temporary_animation.c
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
normal! 013|
wincmd w
exe 'vert 1resize ' . ((&columns * 87 + 91) / 182)
exe 'vert 2resize ' . ((&columns * 94 + 91) / 182)
tabnext
edit entity.c
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
exe 'vert 1resize ' . ((&columns * 87 + 91) / 182)
exe 'vert 2resize ' . ((&columns * 94 + 91) / 182)
argglobal
balt entity.h
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 268 - ((49 * winheight(0) + 26) / 52)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 268
normal! 0
wincmd w
argglobal
if bufexists("entity.h") | buffer entity.h | else | edit entity.h | endif
balt entity.c
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 50 - ((46 * winheight(0) + 26) / 52)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 50
normal! 034|
wincmd w
exe 'vert 1resize ' . ((&columns * 87 + 91) / 182)
exe 'vert 2resize ' . ((&columns * 94 + 91) / 182)
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
exe 'vert 1resize ' . ((&columns * 102 + 91) / 182)
exe 'vert 2resize ' . ((&columns * 79 + 91) / 182)
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
let s:l = 44 - ((36 * winheight(0) + 26) / 52)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 44
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
let s:l = 68 - ((42 * winheight(0) + 26) / 52)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 68
normal! 020|
wincmd w
exe 'vert 1resize ' . ((&columns * 102 + 91) / 182)
exe 'vert 2resize ' . ((&columns * 79 + 91) / 182)
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
exe 'vert 1resize ' . ((&columns * 164 + 91) / 182)
exe 'vert 2resize ' . ((&columns * 17 + 91) / 182)
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
let s:l = 7 - ((6 * winheight(0) + 26) / 52)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 7
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
let s:l = 31 - ((30 * winheight(0) + 26) / 52)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 31
normal! 0
wincmd w
exe 'vert 1resize ' . ((&columns * 164 + 91) / 182)
exe 'vert 2resize ' . ((&columns * 17 + 91) / 182)
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
exe 'vert 1resize ' . ((&columns * 131 + 91) / 182)
exe 'vert 2resize ' . ((&columns * 50 + 91) / 182)
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
let s:l = 204 - ((33 * winheight(0) + 26) / 52)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 204
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
let s:l = 24 - ((23 * winheight(0) + 26) / 52)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 24
normal! 020|
wincmd w
exe 'vert 1resize ' . ((&columns * 131 + 91) / 182)
exe 'vert 2resize ' . ((&columns * 50 + 91) / 182)
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
exe 'vert 1resize ' . ((&columns * 116 + 91) / 182)
exe 'vert 2resize ' . ((&columns * 65 + 91) / 182)
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
let s:l = 137 - ((27 * winheight(0) + 26) / 52)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 137
normal! 039|
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
let s:l = 51 - ((38 * winheight(0) + 26) / 52)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 51
normal! 010|
wincmd w
exe 'vert 1resize ' . ((&columns * 116 + 91) / 182)
exe 'vert 2resize ' . ((&columns * 65 + 91) / 182)
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
exe 'vert 1resize ' . ((&columns * 93 + 91) / 182)
exe 'vert 2resize ' . ((&columns * 88 + 91) / 182)
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
let s:l = 289 - ((24 * winheight(0) + 26) / 52)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 289
normal! 017|
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
let s:l = 51 - ((33 * winheight(0) + 26) / 52)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 51
normal! 026|
wincmd w
exe 'vert 1resize ' . ((&columns * 93 + 91) / 182)
exe 'vert 2resize ' . ((&columns * 88 + 91) / 182)
tabnext
edit memory.c
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
exe 'vert 1resize ' . ((&columns * 105 + 91) / 182)
exe 'vert 2resize ' . ((&columns * 76 + 91) / 182)
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
let s:l = 127 - ((51 * winheight(0) + 26) / 52)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 127
normal! 0
wincmd w
argglobal
if bufexists("memory.h") | buffer memory.h | else | edit memory.h | endif
balt memory.c
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 36 - ((29 * winheight(0) + 26) / 52)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 36
normal! 013|
wincmd w
exe 'vert 1resize ' . ((&columns * 105 + 91) / 182)
exe 'vert 2resize ' . ((&columns * 76 + 91) / 182)
tabnext
edit input.c
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
exe 'vert 1resize ' . ((&columns * 118 + 91) / 182)
exe 'vert 2resize ' . ((&columns * 63 + 91) / 182)
argglobal
balt input.h
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 104 - ((27 * winheight(0) + 26) / 52)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 104
normal! 0
wincmd w
argglobal
if bufexists("input.h") | buffer input.h | else | edit input.h | endif
balt input.c
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 24 - ((18 * winheight(0) + 26) / 52)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 24
normal! 023|
wincmd w
exe 'vert 1resize ' . ((&columns * 118 + 91) / 182)
exe 'vert 2resize ' . ((&columns * 63 + 91) / 182)
tabnext
edit graphics.c
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
exe 'vert 1resize ' . ((&columns * 116 + 91) / 182)
exe 'vert 2resize ' . ((&columns * 65 + 91) / 182)
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
let s:l = 94 - ((22 * winheight(0) + 26) / 52)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 94
normal! 041|
wincmd w
argglobal
if bufexists("graphics.h") | buffer graphics.h | else | edit graphics.h | endif
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
let s:l = 72 - ((49 * winheight(0) + 26) / 52)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 72
normal! 0
wincmd w
exe 'vert 1resize ' . ((&columns * 116 + 91) / 182)
exe 'vert 2resize ' . ((&columns * 65 + 91) / 182)
tabnext
edit audio.c
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
exe 'vert 1resize ' . ((&columns * 105 + 91) / 182)
exe 'vert 2resize ' . ((&columns * 76 + 91) / 182)
argglobal
balt audio.h
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 31 - ((27 * winheight(0) + 26) / 52)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 31
normal! 047|
wincmd w
argglobal
if bufexists("audio.h") | buffer audio.h | else | edit audio.h | endif
balt audio.c
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 22 - ((21 * winheight(0) + 26) / 52)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 22
normal! 032|
wincmd w
exe 'vert 1resize ' . ((&columns * 105 + 91) / 182)
exe 'vert 2resize ' . ((&columns * 76 + 91) / 182)
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
let s:l = 1158 - ((51 * winheight(0) + 26) / 53)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 1158
normal! 0
lcd ~/Work/dungeon-crawl
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
exe 'vert 1resize ' . ((&columns * 131 + 91) / 182)
exe 'vert 2resize ' . ((&columns * 50 + 91) / 182)
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
let s:l = 110 - ((27 * winheight(0) + 26) / 52)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 110
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
let s:l = 2 - ((1 * winheight(0) + 26) / 52)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 2
normal! 0
wincmd w
exe 'vert 1resize ' . ((&columns * 131 + 91) / 182)
exe 'vert 2resize ' . ((&columns * 50 + 91) / 182)
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
exe 'vert 1resize ' . ((&columns * 164 + 91) / 182)
exe 'vert 2resize ' . ((&columns * 17 + 91) / 182)
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
let s:l = 2 - ((1 * winheight(0) + 26) / 52)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 2
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
let s:l = 22 - ((21 * winheight(0) + 26) / 52)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 22
let s:c = 24 - ((0 * winwidth(0) + 8) / 17)
if s:c > 0
  exe 'normal! ' . s:c . '|zs' . 24 . '|'
else
  normal! 024|
endif
wincmd w
exe 'vert 1resize ' . ((&columns * 164 + 91) / 182)
exe 'vert 2resize ' . ((&columns * 17 + 91) / 182)
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
exe 'vert 1resize ' . ((&columns * 164 + 91) / 182)
exe 'vert 2resize ' . ((&columns * 17 + 91) / 182)
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
let s:l = 3 - ((2 * winheight(0) + 26) / 52)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 3
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
let s:l = 43 - ((33 * winheight(0) + 26) / 52)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 43
normal! 0
wincmd w
exe 'vert 1resize ' . ((&columns * 164 + 91) / 182)
exe 'vert 2resize ' . ((&columns * 17 + 91) / 182)
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
exe 'vert 1resize ' . ((&columns * 164 + 91) / 182)
exe 'vert 2resize ' . ((&columns * 17 + 91) / 182)
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
let s:l = 16 - ((15 * winheight(0) + 26) / 52)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 16
normal! 014|
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
let s:l = 17 - ((16 * winheight(0) + 26) / 52)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 17
normal! 0
wincmd w
exe 'vert 1resize ' . ((&columns * 164 + 91) / 182)
exe 'vert 2resize ' . ((&columns * 17 + 91) / 182)
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
normal! 0
tabnext 12
set stal=1
badd +1 ~/Work/dungeon-crawl/transform.c
badd +1 ~/Work/dungeon-crawl/animation.c
badd +83 ~/Work/dungeon-crawl/temporary_animation.c
badd +1 ~/Work/dungeon-crawl/entity.c
badd +1 ~/Work/dungeon-crawl/game.c
badd +1 ~/Work/dungeon-crawl/active.c
badd +1 ~/Work/dungeon-crawl/map.c
badd +1 ~/Work/dungeon-crawl/item.c
badd +1 ~/Work/dungeon-crawl/creature.c
badd +1 ~/Work/dungeon-crawl/memory.c
badd +1 ~/Work/dungeon-crawl/input.c
badd +1 ~/Work/dungeon-crawl/graphics.c
badd +1 ~/Work/dungeon-crawl/audio.c
badd +1 /usr/include/SDL2/SDL_render.h
badd +1 ~/Work/dungeon-crawl/ui.c
badd +1 ~/Work/dungeon-crawl/utils.c
badd +1 ~/Work/dungeon-crawl/vector.c
badd +1 ~/Work/dungeon-crawl/tests.c
badd +1 ~/Work/dungeon-crawl/build.sh
badd +25 ~/Work/dungeon-crawl/utils.h
badd +35 ~/Work/dungeon-crawl/transform.h
badd +1 ~/Work/dungeon-crawl/transform_data.h
badd +1 ~/Work/dungeon-crawl/animation.h
badd +1 ~/Work/dungeon-crawl/temporary_animation.h
badd +1 ~/Work/dungeon-crawl/entity.h
badd +1 ~/Work/dungeon-crawl/game.h
badd +1 ~/Work/dungeon-crawl/active.h
badd +42 ~/Work/dungeon-crawl/map.h
badd +41 ~/Work/dungeon-crawl/item.h
badd +19 ~/Work/dungeon-crawl/\'
badd +1 ~/Work/dungeon-crawl/creature.h
badd +20 ~/Work/dungeon-crawl/memory.h
badd +42 ~/Work/dungeon-crawl/input.h
badd +40 ~/Work/dungeon-crawl/graphics.h
badd +1 ~/Work/dungeon-crawl/audio.h
badd +1 /usr/include/SDL2
badd +13 ~/Work/dungeon-crawl/ui.h
badd +1 ~/Work/dungeon-crawl/vector.h
badd +1 ~/Work/dungeon-crawl/tests.h
badd +196 ~/Work/dungeon-crawl/kiss_sdl/kiss_general.c
badd +1 ~/Work/dungeon-crawl/kiss_sdl/kiss_sdl.h
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
badd +45 ~/Work/dungeon-crawl/kiss_sdl/kiss_LICENSE
badd +46 ~/Work/dungeon-crawl/kiss_sdl/kiss_draw.c
badd +27 ~/Work/dungeon-crawl/kiss_sdl/kiss_example1.c
badd +64 ~/Work/dungeon-crawl/kiss_sdl/kiss_example2.c
badd +1321 ~/Work/dungeon-crawl/kiss_sdl/kiss_font.ttf
badd +271 ~/Work/dungeon-crawl/kiss_sdl/kiss_widgets.c
badd +1 ~/Work/dungeon-crawl/Animation
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
