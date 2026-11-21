# TODO

## OLS Baseline Tests

Status: Active

Contract:

- Input is whitespace-separated numeric data with a fixed number of values per row.
- The caller provides the feature count; the final value in each row is the target.
- The loader returns failure for IO/parse/allocation errors or an incompatible total value count.
- The loader assumes rows follow the sklearn-generated format; do not add general schema handling yet.

Next actions:

- Add a small loader test that checks feature dimensions and target values.
- Add a deterministic OLS test that checks known coefficients and prediction error.

Decision note:

- Keep the example's IO path small and reuse the feature/target reader.
- Defer ragged-row and arbitrary-file diagnostics until non-generated input is supported.

Revisit trigger:

- Add support for hand-authored or externally sourced datasets.

## API Error Semantics (Pinned)

Status: Deferred (intentionally pinned)

Current behavior in vector API:

- Invalid vector inputs often return safe fallback values.
- Vector-returning functions typically return an empty vector (`size = 0`, `data = NULL`).
- Scalar-returning functions (`dot`, `norm`, `cosine_similarity`) return `0.0` on invalid input.
- `cosine_similarity` currently returns `0.0` when denominator is zero.

Why this is deferred:

- It is acceptable and idiomatic for early-stage C libraries.
- The current priority is validating the OLS baseline.
- We may later need stricter error signaling when API surface grows.

Revisit later options:

1. Keep fallback contract as-is and document clearly.
2. Add checked variants with status return + out parameter (for example `int dot_checked(..., double *out)`).
3. Introduce a small error enum for library-wide consistency.

Trigger to revisit:

- First external consumer or a need for consistent library-wide diagnostics.

Decision note:

- No exceptions in C. Use explicit return contracts and/or status codes when needed.
