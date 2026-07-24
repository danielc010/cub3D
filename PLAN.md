# My Parser Plan (Partner A) — cub3D

Working method for every phase: **explain → attempt → review.**
Ask for the concept first, write my own draft, then ask for a critique — not a rewrite.

---

## Phase 0 — Contract (with partner, before coding)
- [ ] Write `cub3d.h` together, by hand, field by field
- [ ] Sign off on the contract table (texture indices, color format, coordinate system, MLX ownership)
- [ ] Self-check: can I explain why `grid[0][0]` is top-left and what that means for movement?

Branch: none yet (shared work)

---

## Phase 1 — File reading & argument validation
Files: `srcs/parse/parse.c`
Learn first: safe line-by-line file reading, why validate `argv[1]` and `.cub` extension before anything else, fail-fast error philosophy.

- [ ] Validate argc, extension, file opens
- [ ] Read all lines into memory
- [ ] Decide: parse in one pass, or store raw lines first? (ask Claude to explain the tradeoff before deciding)

Branch: `feat/parser` or `feat/parse-map`

---

## Phase 2 — Texture paths (NO/SO/EA/WE)
Files: `srcs/parse/parse_textures.c`
Learn first: string parsing pitfalls, detecting duplicate/missing identifiers, how `mlx_load_png()` will consume the path.

- [ ] Extract paths for all four identifiers
- [ ] Handle missing / duplicate / malformed lines as errors
- [ ] Store into `t_map.tex[TEX_NO..TEX_WE]` using header constants, not raw numbers

Branch: `feat/parse-textures`

---

## Phase 3 — Floor & ceiling colors
Files: `srcs/parse/parse_textures.c` (or split out)
Learn first: bit-shifting math to pack R,G,B decimal ints into `0xRRGGBBAA`.

- [ ] Self-check: pack `(255, 128, 0)` into the correct hex by hand before coding
- [ ] Implement the packing function
- [ ] Validate R/G/B are in range 0–255, handle malformed color lines

Branch: `feat/parse-colors`

---

## Phase 4 — Map grid parsing & storage
Files: `srcs/parse/parse_map.c`
Learn first: why the map must be the last section, detecting where it starts, why `char **grid` (not fixed 2D array) given variable width.

- [ ] Locate map start
- [ ] Copy remaining lines into `grid`, handle ragged row widths
- [ ] Validate only allowed characters appear (`0 1 N S E W space`)

Branch: `feat/parse-map`

---

## Phase 5 — Map validation (flood fill)
Files: `srcs/parse/parse_map.c` or new file
Learn first: flood fill concept with a small example, recursive vs iterative and why recursion risks stack overflow on large maps.

- [ ] Implement flood fill from player position
- [ ] Invalid if it reaches map edge or an undefined cell
- [ ] Test against a map with a deliberate hole in the wall

Branch: `feat/flood-fill`

---

## Phase 6 — Player detection & direction vectors
Files: `srcs/parse/parse_map.c`
Learn first: how N/S/E/W map to `(dir_x, dir_y)` and `(plane_x, plane_y)`, the FOV=0.66 camera plane math — work it out on paper first.

- [ ] Scan for exactly one player marker (error on 0 or 2+)
- [ ] Set `player.x`/`player.y` to cell center (`col + 0.5`, `row + 0.5`)
- [ ] Derive direction + camera plane vectors from the letter

Branch: `feat/parser`

---

## Phase 7 — Error handling (ongoing, not a separate block)
Files: `srcs/utils/errors.c`
Write `error_exit()` in Phase 1, not last. Every phase above calls it rather than accumulating ad-hoc handling.

- [ ] `error_exit()` written early
- [ ] Every parse failure path calls it consistently

---

## Phase 8 — Memory & `free_game()`
Files: `srcs/utils/free.c`
Do incrementally — after each phase, ask "does `free_game()` already cover what I just malloc'd?"

- [ ] Run valgrind after each phase, not just at the end
- [ ] `free_game()` covers every allocation before submission

---

## Phase 9 — First integration
- [ ] Swap `load_debug_map()` for `parse()` in `main.c` together with partner
- [ ] Verify map, textures, colors, player fields render correctly
- [ ] If it breaks: check color format, texture index order, direction vector init — in that order

---

## Standing habits (whole project)
- [ ] Run norminette after every function
- [ ] Explain out loud / in commit message what a function needs to do before asking for code
- [ ] Commit small, pull partner's branch daily
