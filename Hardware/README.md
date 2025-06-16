# Hardware

This folder contains all electrical and mechanical design files for the Romi++ Differential Drive Robot, including PCB schematics, board layout, manufacturing assets, and mechanical CAD models.

## Contents

### `Electrical/` – Fusion PCB design files, manufacturing exports, and board reference images

- `JLCPCB Order Info/` – Gerber files, bill of materials (BOM), and pick-and-place data for PCB fabrication, see notes for more info
- `PCB Design Files/` – Schematic (`.sch`), board layout (`.brd`), 3D model (`.step`), and full Fusion 360 project archive (`.f3z`)
- Additional Files – Reference images of the board (front, back, isometric), schematic and layout PDFs

### `Mechanical/` – SolidWorks CAD files, 3D-printable models, and robot images

- `SolidWorks 2024 Part Files/` – Native `.SLDPRT` and `.SLDASM` files, including McMaster-Carr fasteners and vendor-supplied STEP models
- `STL 3-D Print Files/` – Exported `.stl` files ready for 3D printing
- `Robot BOM.csv` - Bill of materials for the mechanical assembly, see notes for more info
- Additional Files – Images of the robot: CAD view, and pictures of the assembled robot

---

## How to Open the Files

### SolidWorks Files

1. Launch **SolidWorks 2024** or compatible version
2. Open `.SLDASM` files from `SolidWorks 2024 Part Files/`
3. Make sure subfolders (e.g., fasteners, STEP parts) are in the same root for proper assembly resolution

### Fusion 360 Files

1. Open Fusion 360
2. Go to **File → Open**
3. Select `ME 507 Romi++.f3z` to import the PCB project including schematic and layout

---

## Notes

- Mechanical Notes
    - Components not included in BOM were provided by my instructor
    - 20  8mm M3 Screws
    - 12 10mm M3 Screws
    - 12 12mm M3 Screws
    - 44 M3 Washers (.5mm thick)
    -  8 M3 Hex Nuts
- Electrical notes
    - For the JLCPCB order, some PCB components needed to be adjusted. This consisted of rotating some parts into the correct orientation seen on my board layout. For any recreations of this project, it is highly recommended to have the manufacturer review the design for you before assembly begins.
