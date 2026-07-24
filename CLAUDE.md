# cub3D — Project Context for Claude Code

## Who's who
- **Daniel (me) = Partner A: Parser & World.** I write everything under `srcs/parse/`, `srcs/utils/errors.c`, `srcs/utils/free.c`, and the `Makefile`.
- **Partner B: Engine & Renderer.** Owns `srcs/engine/`. I should never write or fix code in that folder — flag it instead and let my partner handle it.
- This is a deliberate role swap from my last 42 project (minishell), where I did execution and my partner did lexer/parser/expander. I'm intentionally taking the less-familiar role here to learn parsing/data-structuring, not the path of least resistance.

## How I want Claude Code to work with me on this project

**Primary goal: I learn while I code, not just ship working code.** Concretely:

1. **Don't write full function implementations unless I explicitly ask for the final version.** Default to:
   - Explaining the concept/algorithm first, in plain language, with no code
   - Letting me write a first attempt
   - Reviewing what I wrote — point out bugs, edge cases, norm violations — rather than rewriting it for me
2. If I ask "how does X work" — explain it, don't just implement it.
3. If I paste code and ask for a review — critique it, suggest fixes, but let me make the edits myself where reasonable.
4. Flag norminette violations (max 25 lines/function, max 5 functions/file, no `for` loops, no declarations after statements) as soon as you see them, not at the end.
5. Never touch `srcs/engine/` — that's Partner B's code.
6. Treat `includes/cub3d.h` as a shared contract — flag it clearly if a change I want would affect Partner B's side, and remind me to sync with them before committing it.

## Git strategy
- Primary branch: `feat/parser`
- Optional sub-branches if collision risk increases: `feat/parse-map`, `feat/parse-textures`, `feat/parse-colors`, `feat/flood-fill`, `feat/error-handling`
- Commit small and often; pull partner's engine branch changes daily to stay in sync.

## The shared contract (cub3d.h) — key agreed values
- Texture indices: `NO=0 SO=1 EA=2 WE=3`
- Color format: `0xRRGGBBAA`, alpha always `0xFF`
- Map coordinates: `grid[row][col]`, `(0,0)` = top-left
- Player position/direction: **I (A) set it from the map letter**, Partner B only reads it
- `error_exit(game, msg)`: I write it, both partners call it — prints to stderr, frees everything, exits 1
- `is_wall(map, x, y)`: I write it with bounds checking, Partner B calls it
- MLX lifecycle: **Partner B calls `mlx_init()` before `parse()`** — I never call it

Full struct definitions for `t_game`, `t_player`, `t_map`, `t_texture` live in `includes/cub3d.h` — treat that file as the single source of truth, don't duplicate struct knowledge here that could drift out of sync.

## My task breakdown (Partner A)
See `PLAN.md` in this repo for the full phase-by-phase breakdown with learning goals per phase.

## Common integration failure points (check these first if something breaks after merging with Partner B)
1. Color format mismatch (RGBA vs ARGB ordering)
2. Texture index order mismatch (who is index 0?)
3. Player direction vector not initialized correctly by me (A)

## Debug stub note
Partner B uses `srcs/engine/debug_map.c` as a stand-in for my parser during early development. The moment `parse()` fills `t_game` even partially, we integrate — don't wait for the parser to be "done."
