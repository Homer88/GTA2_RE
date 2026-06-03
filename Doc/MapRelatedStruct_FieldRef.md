# MapRelatedStruct Field Cross-Reference

## Layout (offsets from `this`)

| Offset | Size | IDA Name | Actual Type | Description | Key Methods |
|--------|------|----------|-------------|-------------|-------------|
| 0x000 | 4 | `Map` | `Map*` | Pointer to Map struct (tile grid + buffers) | `sub_4646A0` (alloc), `sub_464B30` (free), `FindMaxZForTile`, `sub_4653C0` (read tile) |
| 0x004 | 804 | `S16_01` | `S16_01` | Embedded zone-indexing sub-object | `S16_01::S16_01` (ctor), accessed via `sub_462E40` |
| 0x004..0x31F | — | `S16_01.gap0[800]` | `_BYTE[800]` | Gap — some bytes accessed as `field_314`, `field_318`, `field_31C`, `field_320` | Constructor sets 0x314/0x318/0x31C/0x320 to 0 |
| 0x324 | 4 | `S16_01.field_320` | `int` | Offset-LUT pointer within S16_01 | `sub_462C60`, all `sub_462CB0`-based methods |
| 0x328 | 4 | `Buffer_ZONE` | `FILE*` | Allocated ZONE chunk data buffer | `sub_464B30` (free), `sub_462E40` (read entry) |
| 0x32C | 4 | `count` [was `int`] | `int*` / `FILE*` | **Pointer** to count value (was mis-declared as `int`) | `sub_464B30` (free), `sub_462E40` checks `*(_WORD *)count` |
| 0x330 | 4 | `field_330` | `FILE*` | ZONE data buffer (allocated) | `sub_464B30` (free), `sub_462E40` (string lookup offset base) |
| 0x334 | 4 | `field_334` | `FILE*` | ZONE string table (allocated) | `sub_464B30` (free), `sub_462E40` (string data base) |
| 0x338 | 4 | `Buffer_MOBJ` | `FILE*` | MOBJ chunk buffer (allocated) | `sub_464B30` (free), `sub_46A4D0` (iterate & spawn) |
| 0x33C | 4 | `Buffer_LGHT` | `FILE*` | LGHT chunk buffer (allocated) | `sub_464B30` (free) |
| 0x340 | 4 | `Buffer_ANIM` | `FILE*` | ANIM chunk buffer (allocated) | `sub_464B30` (free) |
| 0x344 | 4 | `field_344` | `int` | Number of MOBJ entries | `sub_46A4D0` (loop bound) |
| 0x348 | 4 | `field_348` | `int` | Number of ANIM entries | |
| 0x34C | 4 | `field_34C` | `int` | Tile data count (from file) | `sub_4646A0` (set = `Map->field_40004`) |
| 0x350 | 4 | `field_350` | `int` | Tile data capacity (`field_40004 + 200`) | `sub_4646A0` (set) |
| 0x354 | 4 | `field_354` | `int` | Tile data count (copy of `field_34C`) | `sub_4646A0` (set), used in save/load for size calc |
| 0x358 | 4 | `field_358` | `int` | Tile index count (from file) | `sub_4646A0` (set) |
| 0x35C | 4 | `field_35C` | `int` | Tile index capacity (from file) | `sub_4646A0` (set = `File[256]`) |
| 0x360 | 4 | `field_360` | `int` | Dynamic tile index counter | `sub_4646A0` (init), adjusted on edit |
| 0x364 | 2 | `field_364` | `ushort` | ZONE iterator index | `sub_462E40` (iterate), `sub_462CB0` (compare current) |
| 0x366 | 2 | `field_366` | `__int16` | (unknown) | Constructor sets to 0 |
| 0x368 | 1 | `Len` | `char` | String length for matching | `sub_462F50` (compare with entry name[0]) |
| 0x369 | 1 | `field_369` | `char` | Initialised to -1 in ctor | Constructor |
| 0x36A | 1 | `field_36A` | `char` | String match byte 0 | `sub_462F50` (compare with entry name) |
| 0x36B | 1 | `field_36B` | `char` | String match byte 1 | `sub_462F50` (compare with entry name) |
| 0x36C | 1 | `field_36C` | `char` | Match flag (bool) | `sub_462F50` (check match) |
| 0x36D | 1 | `field_36D` | `char` | (unknown) | Constructor sets to 0 |
| 0x36E | 1 | `field_36E` | `char` | Processing flag (bool) | Set to 1 in several chunk loaders |
| 0x36F | 1 | `field_36F` | `char` | Another flag (bool) | `sub_464DA0`, `sub_464E70` |

## Field Access Patterns (by method groups)

### Map tile I/O
| Method | Fields Accessed | External Globals | Notes |
|--------|----------------|------------------|-------|
| `sub_4646A0` | **Map** (alloc), **field_35C**, **field_358**, **field_360**, **field_350**, **field_34C**, **field_354** | `createBuffer`, `FileMgr::Read`, `operator_new` | Loads `.MAP` file; sets tile index/data buffer sizes |
| `sub_464990` | **Map** → `sub_4646A0` (transitive) | `FileMgr::Open` | Opens map file by name, delegates to `sub_4646A0` |

### Tile queries
| Method | Fields Accessed | External Globals | Notes |
|--------|----------------|------------------|-------|
| `FindMaxZForTile` | **Map** → `field_40008`, `field_4000C` | `dword_662B90` | Scans tile index/data buffers for tile with non-zero type |
| `FindMaxZForLocation` | → calls `FindMaxZForTile`, `sub_466B70` | — | Wraps `FindMaxZForTile` with S202 handling |
| `sub_4653C0` | **Map** → `field_4000C`, `field_40008` | `dword_662B90` | Core tile lookup — most-called method |
| `sub_463570` | **Map** → `field_40008` | — | Tile query with DWORD out-param |
| `sub_4635F0` | **Map** → `field_40008` | — | Tile query with int out-param |
| `sub_463A00` | **Map** → `field_4000C` | — | Read tile data at index |
| `sub_463A40` | **Map** → `field_4000C` | — | Read tile height byte |
| `sub_463A90` | **Map** → `field_40008` | — | Read tile index |
| `sub_463AE0` | **Map** → `field_40008` | — | Write tile index |
| `sub_463C30` | **Map** → `field_40008`, `field_4000C` | — | Swap tile index, copy tile data |
| `sub_463F60` | **Map** → `field_40008`, `field_4000C` | — | Set tile type in data buffer |
| `sub_464060` | **Map** → `field_40008`, `field_4000C` | — | Set tile index and data |
| `sub_464110` | **Map** → `field_40008` | — | Insert tile index |
| `sub_464250` | **Map** → `field_40004`, `field_40008`, `field_4000C` | — | Map pointer as `Map**this` |
| `sub_4642A0` | **Buffer_ZONE**, **count**, **field_330**, **field_334**, **Map** → `File`, `field_40004`, `field_40008`, `field_4000C` | `FileMgr`, `free_0`, `createBuffer` | Save/load (exported as `MapRelatedStruct_sub_4642A0`) |

### ZONE iteration / string-keyed lookup
| Method | Fields Accessed | Notes |
|--------|----------------|-------|
| `sub_462E40` | **Buffer_ZONE**, **count**, **field_330**, **field_334**, **field_364** | Core ZONE entry lookup by index; reads from field_330/field_334 buffer |
| `sub_462CB0` | **field_364** | Compare/advance iterator |
| `sub_462C60` | **S16_01** → `field_320` | Returns `field_320 + 1` |
| `sub_462CE0`–`sub_462E20` (11 methods) | → `sub_462CB0` | All thin wrappers over `sub_462CB0` |
| `sub_462E80` | **Buffer_ZONE** | Check if ZONE is loaded |
| `sub_462F50` | **Buffer_ZONE**, **count**, **Len**, **field_36A**, **field_36B**, **field_36C**, **field_364** | Match ZONE entry name against Len/field_36A/field_36B |
| `sub_4632E0` | → `sub_4633A0` | |
| `sub_4633A0` | → `sub_462E40`, → `sub_4653C0` | |
| `sub_464C70` | → `sub_462E40` | Lookup by name string (exported) |
| `sub_464D00` | **field_364** | Set index from name + hash |
| `sub_464DA0` | **field_36F**, → `sub_462E40` | Find entry with type matching a2 |
| `sub_464E70` | **field_36F**, → `sub_464DA0` | Find next entry of type; sets field_36F=1 |
| `sub_464FE0` | → `sub_462E40` | 3-key lookup (a2, a3, a4) |
| `sub_465090` | → `sub_462E40` | 2-key lookup |
| `sub_465130` | → `sub_462E40` | 2-key lookup (different) |
| `sub_4651C0` | → `sub_464DA0` | Iterate next ZONE entry (resets field_36F) |

### Map effects (audio, collision)
| Method | Fields Accessed | Notes |
|--------|----------------|-------|
| `sub_465FE0` | **Map**, **S16_01** | Refit tile to grid; calls `sub_4653C0`, `sub_466B70` |
| `sub_466170` | **Map** | Check tile effect; calls `sub_4653C0` |
| `sub_466380` | → `sub_465410` | Effect spread (5-neighbor); calls `sub_466B70` |
| `sub_466430` | → `sub_465410` | Effect spread (4-neighbor); calls `sub_466B70` |
| `sub_466620` | **Map** | Check tile height; calls `sub_4653C0` |
| `sub_466730` | → `sub_4653C0`, → `sub_466B70` | Audio effect at tile |
| `sub_466910` | **Map** | Tile type check; calls `sub_4653C0` |
| `sub_466AF0` | → `sub_4653C0` | Game entity at tile check |
| `sub_466B70` | → `sub_4653C0` | Set effect on tile |
| `sub_466CF0` | → `sub_4653C0` | Tile adjacency check (bool) |
| `sub_466D30` | → `sub_4653C0`, → `sub_466CF0` | Audio validation |
| `sub_466E20` | → `sub_466CF0`, → `sub_466B70`, → `sub_4635F0` | Audio validation with fallback |
| `sub_466F70` | → `sub_463570`, → `sub_466B70` | Audio source query |
| `sub_467110` | → `sub_467020`, `sub_4653C0`, `sub_4633A0`, `sub_4632E0` | Car AI tile scanning |
| `sub_467F80` | → `sub_467020`, `sub_4653C0`, `sub_4633A0`, `sub_4632E0` | Car AI tile scanning (ped variant) |

### Audio-related queries
| Method | Fields Accessed | Notes |
|--------|----------------|-------|
| `sub_463850` | **Map** | Audio param check at tile; calls `sub_4653C0` |
| `sub_469110` | → `sub_462E40` | Audio source name lookup |
| `sub_4692B0` | → `sub_466910` | Rebuild audio world ties |
| `sub_469570` | → `sub_466CF0`, → `sub_466B70` | Audio source + adjacency |
| `sub_4696C0` | → `sub_4653C0`, → `sub_466B70` | Audio source update |
| `sub_469850` | → `sub_466CF0`, → `sub_466B70`, → `sub_466A00` | Audio source update |
| `sub_4699A0` | → `sub_466CF0`, → `sub_466B70`, → `sub_466A00` | Audio validation |
| `sub_469B00` | → `sub_4653C0`, → `sub_466B70` | Audio effect at entity |
| `sub_469C20` | → `sub_4653C0`, → `sub_466B70` | Audio effect check |
| `sub_469DC0` | → `sub_4653C0`, → `sub_466B70` | Audio effect update |
| `sub_469F90` | → `sub_466CF0`, → `sub_466B70` | Audio spread check |

### Car AI
| Method | Fields Accessed | Notes |
|--------|----------------|-------|
| `sub_46A4D0` | **Buffer_MOBJ**, **field_344** | Spawn objects from MOBJ; calls `FindMaxZForLocation` |
| `sub_46A570` | → `sub_469B00`, → `sub_466CF0`, → `sub_466430` | Car move validation |
| `sub_46B440` | → `sub_46A570` | Car move with tuning |

### Tile boundary checks (sub_42A850-based)
| Method | Calls | Returns true when tile data byte 11 & 3 == |
|--------|-------|-------------------------------------------|
| `sub_42A850` | — | (raw tile data pointer) |
| `sub_42A8C0` | `sub_42A850(this, a2, a3, a4)` | 1 |
| `sub_433430` | `sub_42A850(this, a2, a3, a4)` | (check variant) |
| `sub_433470` | `sub_42A850(this, a2-1, a3, a4)` | 1 |
| `sub_4334A0` | `sub_42A850(this, a2, a3-1, a4)` | 1 |
| `sub_4334D0` | `sub_42A850(this, a2+1, a3, a4)` | 1 |
| `sub_433500` | `sub_42A850(this, a2, a3+1, a4)` | 1 |
| `sub_433530` | `sub_42A850(this, a2, a3, a4)` | 2 |

### Globals used by MapRelatedStruct methods
| Global | Type | Written by | Read by |
|--------|------|--------|--------|
| `dword_662B90` | `_WORD*` | `FindMaxZForTile`, `sub_466A00`, `sub_466D30`, `sub_4653C0` | `FindMaxZForTile`, `sub_466A00`, `sub_466D30` |
| `gMapRelatedStruct` | `MapRelatedStruct*` | — | All external callers |
| `unk_662B94` | `S16_02` | Constructor | `sub_466E20`, `sub_467F80`, `sub_469570`, `sub_4696C0` |
| `unk_662BC0` | `S16_02` | Constructor | `sub_466E20`, `sub_469570`, `sub_4696C0` |
| `unk_662B9C` | `char` | Constructor (=1) | — |
| `unk_662B9F` | `char` | Constructor (=3) | — |
