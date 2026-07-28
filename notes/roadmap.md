# Roadmap

This file is intended to evolve as project priorities change.

## Near-Term Goal

1. Implement linear regression in C using current matrix/vector tools.

## Next Milestones

1. Define strict dataset file contract for C ingestion.
2. Implement minimal C data loader for numeric training data.
3. Build design matrix X and target vector y in C.
4. Compute normal equation components (X^T X, X^T y).
5. Solve for coefficients with solve_gauss_elimination.
6. Report coefficients and training MSE from a C example.

## Follow-Up Milestones

1. Add focused C tests for solver and linear regression pipeline.
2. Improve IO ergonomics (clear errors, shape validation).
3. Evaluate regularized linear regression after baseline is stable.
