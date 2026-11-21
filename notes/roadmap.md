# Roadmap

This file is intended to evolve as project priorities change.

## Near-Term Goal

1. Implement a runnable linear regression baseline in C using current matrix/vector tools.

## Next Milestones

1. Define and document the dataset file contract for C ingestion.
2. Implement minimal C data loader for numeric training data with row/column validation.
3. Add focused C tests for loader happy path and malformed-row failures.
4. Build design matrix X and target vector y in C from loaded data.
5. Compute normal equation components (X^T X, X^T y).
6. Solve for coefficients with solve_gauss_elimination.
7. Report coefficients and training MSE from a C example.

## Follow-Up Milestones

1. Add focused C tests for solver and end-to-end linear regression pipeline.
2. Improve IO ergonomics (clear parse errors, shape validation, and bad-data diagnostics).
3. Evaluate regularized linear regression after baseline is stable.
