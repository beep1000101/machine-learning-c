# TODO

## API Error Semantics (Pinned)

Status: Deferred (intentionally pinned)

Current behavior in vector API:

- Invalid vector inputs often return safe fallback values.
- Vector-returning functions typically return an empty vector (`size = 0`, `data = NULL`).
- Scalar-returning functions (`dot`, `norm`, `cosine_similarity`) return `0.0` on invalid input.
- `cosine_similarity` currently returns `0.0` when denominator is zero.

Why this is deferred:

- It is acceptable and idiomatic for early-stage C libraries.
- We want to focus on matrix functionality next.
- We may later need stricter error signaling when API surface grows.

Revisit later options:

1. Keep fallback contract as-is and document clearly.
2. Add checked variants with status return + out parameter (for example `int dot_checked(..., double *out)`).
3. Introduce a small error enum for library-wide consistency.

Trigger to revisit:

- Start of matrix module stabilization or first external consumer of this API.

Decision note:

- No exceptions in C. Use explicit return contracts and/or status codes when needed.
