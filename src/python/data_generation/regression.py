import numpy as np
from paths import DATA_DIR
from sklearn.datasets import make_regression


def main():
    DATA_DIR.mkdir(parents=True, exist_ok=True)

    features, targets = make_regression(n_samples=100, n_features=3, n_targets=1)
    regression_datapoints = np.column_stack((features, targets))
    file_name = "regression_datapoints.txt"
    file_path = DATA_DIR / file_name
    np.savetxt(fname=file_path, X=regression_datapoints)


if __name__ == "__main__":
    main()
