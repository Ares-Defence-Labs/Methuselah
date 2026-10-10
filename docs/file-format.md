# Draft container format

Provisional development layout, not a stable interchange format. All integers
are fixed-width little-endian; serialization never uses native struct padding.

| Offset | Bytes | Field | Meaning |
| --- | --- | --- | --- |
| 0 | 8 | Magic | ASCII `MTHSLH` followed by CR LF |
| 8 | 2 | Version | `1` |
| 10 | 2 | Header size | `32` |
| 12 | 4 | Flags | Reserved; must be zero |
| 16 | 8 | Metadata size | Bytes following the header |
| 24 | 8 | Payload size | Bytes following metadata |

Header helpers reject bad magic, unsupported versions/flags, incorrect header
sizes, and overflowing total sizes. File inspection reads only the header and
does not verify declared sections exist.

To define: metadata schema, tensor descriptors, alignment, codec/quantization
identifiers, checksums, resource limits, compatibility rules and file extension.
Metadata/payload parsing and writing are not implemented.
