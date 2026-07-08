#!/usr/bin/env bash
set -euo pipefail

ROOT="$(git rev-parse --show-toplevel 2>/dev/null || true)"
if [[ -z "$ROOT" ]]; then
    echo "error: not inside a git repository"
    exit 1
fi
cd "$ROOT"

DRY_RUN=0
DO_PUSH=0
REMOTE="origin"
BRANCH="$(git rev-parse --abbrev-ref HEAD)"

for arg in "$@"; do
    case "$arg" in
        --dry-run) DRY_RUN=1 ;;
        --push) DO_PUSH=1 ;;
        --remote=*) REMOTE="${arg#*=}" ;;
        --branch=*) BRANCH="${arg#*=}" ;;
        *)
            echo "Usage: $0 [--dry-run] [--push] [--remote=<name>] [--branch=<name>]"
            exit 1
            ;;
    esac
done

run() {
    if [[ $DRY_RUN -eq 1 ]]; then
        echo "[dry-run] $*"
    else
        "$@"
    fi
}

stage_and_commit() {
    local msg="$1"
    shift

    local existing=()
    for path in "$@"; do
        if [[ -e "$path" ]]; then
            existing+=("$path")
        fi
    done

    if [[ ${#existing[@]} -eq 0 ]]; then
        return 0
    fi

    run git add -A -- "${existing[@]}"

    if git diff --cached --quiet -- "${existing[@]}"; then
        echo "skip: $msg"
        return 0
    fi

    run git commit -m "$msg" -- "${existing[@]}"
}

cleanup_redundancies() {
    if [[ -f src/algebra/vector.c && -f src/c/algebra/vector.c ]]; then
        if cmp -s src/algebra/vector.c src/c/algebra/vector.c; then
            run git rm -f src/algebra/vector.c
            if [[ -d src/algebra ]]; then
                run rmdir src/algebra || true
            fi
        fi
    fi
}

cleanup_redundancies

stage_and_commit \
    "build(cmake): set up root project and preset workflow" \
    CMakeLists.txt CMakePresets.json examples/CMakeLists.txt examples/algebra/CMakeLists.txt

stage_and_commit \
    "feat(c): add vector module and examples layout" \
    algebra/vector.c algebra/dot_product_example.c src/c/algebra/vector.c src/c/include/algebra/vector.h examples/algebra/vector_example.c examples/algebra/dot_product_example.c

stage_and_commit \
    "build(vscode): compile active file with module include path" \
    .vscode/tasks.json

stage_and_commit \
    "chore(gitignore): ignore build and python artifacts" \
    .gitignore

stage_and_commit \
    "build(python): add src/python package metadata" \
    pyproject.toml src/python/mlc/__init__.py src/python/mlc/wrappers.py

stage_and_commit \
    "docs: add project layout and cmake usage notes" \
    README.md notes/c/cmake-setup.md

stage_and_commit \
    "chore(scripts): add atomic commit helper" \
    scripts/atomic-commit.sh

# Catch remaining changes (including renames/deletions) without losing work.
if ! git diff --quiet || ! git diff --cached --quiet; then
    run git add -A
    if ! git diff --cached --quiet; then
        run git commit -m "chore: apply remaining repository restructuring changes"
    fi
fi

if [[ $DO_PUSH -eq 1 ]]; then
    run git push "$REMOTE" "$BRANCH"
else
    echo "done"
    echo "review: git log --oneline --decorate -n 12"
    echo "push:   git push $REMOTE $BRANCH"
fi
