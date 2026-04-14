# SF2 Custom VDP Demo – 6 bpp Upgrade

**This is a test/demo version** of the enhanced 6 bits-per-pixel VDP for Genesis Plus GX (SF2 Custom fork).

### What Changed in the VDP (Before → After)

| Parameter                   | Was (Original Genesis Plus GX)      | Now (SF2 Custom VDP)                  | Comment |
|-----------------------------|-------------------------------------|---------------------------------------|---------|
| **VRAM**                    | 64 KB                               | **512 KB** (`0x80000`)                | Fully expanded |
| **CRAM**                    | 64 entries × 9-bit                  | **256 entries × 15-bit**              | Full 15-bit color (R5G5B5) |
| **Tile size**               | 32 bytes (4 bpp)                    | **48 bytes (6 bpp)**                  | 6 bits per pixel |
| **VRAM_TILE_SHIFT**         | `<< 5`                              | **`<< 6`**                            | Tile addressing |
| **Palettes**                | 4 × 16 colors                       | **4 × 64 colors**                     | 256 colors total |
| **MARK_BG_DIRTY**           | `<< 5` + 0x7FF                      | `<< 6` + 0x2FFF                       | Updated for 48-byte tiles |
| **render_bg**               | `render_bg_m5`                      | **`render_bg_m5_sf2`**                | Fully 6 bpp |
| **render_obj**              | `render_obj_m5`                     | **`render_obj_m5_sf2`**               | Fully 6 bpp |
| **update_bg_pattern_cache** | `_m5`                               | **`_m5_sf2`**                         | Copies 48 bytes |

### Current Status
- ✅ VRAM expanded to 512 KB + all addressing updated  
- ✅ CRAM upgraded to 256 colors × 15-bit (R5G5B5)  
- ✅ Completely rewritten 6 bpp background and sprite renderer  
- ✅ Full backward compatibility with TMS, Mode 4 and standard Mode 5 games  
- ✅ `color_update_m5` updated for 15-bit color output  

---

### Что изменилось в VDP (до → после)

| Параметр                    | Было (обычный Genesis Plus GX)     | Стало (SF2 Custom VDP)               | Комментарий |
|-----------------------------|------------------------------------|--------------------------------------|-----------|
| **VRAM**                    | 64 КБ                              | **512 КБ** (`0x80000`)               | Полностью расширено |
| **CRAM**                    | 64 записи × 9 бит                  | **256 записей × 15 бит**             | Полноценный 15-битный цвет |
| **Тайл**                    | 32 байта (4 bpp)                   | **48 байт (6 bpp)**                  | 6 бит на пиксель |
| **VRAM_TILE_SHIFT**         | `<< 5`                             | **`<< 6`**                           | Адресация тайлов |
| **Палитры**                 | 4 × 16 цветов                      | **4 × 64 цвета**                     | 256 цветов всего |
| **MARK_BG_DIRTY**           | `<< 5` + 0x7FF                     | `<< 6` + 0x2FFF                      | Под 48-байтные тайлы |
| **render_bg**               | `render_bg_m5`                     | **`render_bg_m5_sf2`**               | Полностью 6 bpp |
| **render_obj**              | `render_obj_m5`                    | **`render_obj_m5_sf2`**              | Полностью 6 bpp |
| **update_bg_pattern_cache** | `_m5`                              | **`_m5_sf2`**                        | Копирует 48 байт |

### Текущий статус
- ✅ VRAM 512 КБ + все адресации  
- ✅ CRAM 256 цветов × 15 бит (R5G5B5)  
- ✅ Полностью переписанный 6 bpp рендер фона и спрайтов  
- ✅ Совместимость со всеми остальными играми (TMS, Mode 4, обычный Mode 5)  
- ✅ `color_update_m5` переделан под 15-битный цвет  

---

**Это тестовая/демо-версия** — расширение VDP до 6 bpp находится в разработке.
