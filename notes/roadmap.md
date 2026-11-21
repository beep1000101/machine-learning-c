# Roadmap

This file is intended to evolve as project priorities change.

## Near-Term Goal

1. Add focused C tests for the runnable linear regression baseline.

## Next Milestones

1. Add a CTest happy-path test for loading features and the final-column target.
2. Add a known-answer OLS test that checks coefficients and prediction error.
3. Keep the end-to-end example using the shared dataset reader and report training MSE.

## Follow-Up Milestones

1. Evaluate a QR-based least-squares solver before increasing feature counts.
2. Evaluate regularized linear regression after the baseline is tested.

## Completed Baseline

1. Read sklearn-style whitespace-separated data into a feature matrix and target vector.
2. Compute normal-equation components and solve for OLS coefficients.
3. Run the C example and report coefficients and training MSE.
