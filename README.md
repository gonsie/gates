# Gate Model

This is a [ROSS](https://github.com/carothersc/ROSS) model for gate-level circuit simulations.

This model uses generic gate LPs, so there is only one ROSS lp-type.
Each gate lp has a specific type (AND, NAND, NOR, etc.) which functionality is refenected via function pointers.

This repo includes an LSI_10k library example.
See the [library.c](https://github.com/gonsie/gates/blob/master/example/lsi_10k.lib.c) file for the gate logic.
