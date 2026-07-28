# Copilot Instructions For Notes

## Purpose

This file defines how notes are written in this repository and why.

Scope: notes only.

Included files:
- notes/roadmap.md
- notes/todo.md
- notes/c/*.md
- notes/private/* (with privacy rules below)

Out of scope:
- Source code style rules for C or Python.
- Build system configuration details beyond note accuracy checks.

## Writing Principles

1. Write for future execution, not for narration.
2. Prefer short, actionable bullets over long prose.
3. Keep one idea per bullet.
4. Keep updates incremental; avoid rewriting entire files unless requested.

Why:
- Notes should reduce cognitive load during implementation sessions.
- Smaller deltas preserve context and make history useful.

## Roadmap Updates

For notes/roadmap.md:

1. Keep milestone-first structure.
2. Use numbered priorities.
3. Keep near-term goals explicit and testable.
4. Move completed items forward by replacing or promoting priorities.

Why:
- A roadmap should answer "what next" in under one minute.
- Numbered priorities force sequencing and reduce context switching.

## Todo Updates

For notes/todo.md:

1. Use status labels (Active, Deferred, Done).
2. Add decision notes when tradeoffs are made.
3. Add revisit triggers for deferred topics.
4. Keep contracts explicit (inputs, outputs, error behavior).

Why:
- Status-driven notes prevent forgotten tasks and ambiguous ownership.
- Revisit triggers make defer decisions intentional instead of permanent.

## C Notes Updates

For notes/c/*.md:

1. Keep commands executable as written.
2. Prefer current preset-based commands when applicable.
3. If a command is environment-specific, mark it clearly.
4. Update command docs when build/debug workflow changes.

Why:
- Command notes are operational docs; incorrect commands waste sessions.

## Private Notes Boundary

For notes/private/*:

1. Treat content as local-only working context.
2. Do not copy private notes into shared notes unless explicitly requested.
3. Keep personal reflections concise and paired with next actions.

Why:
- Private notes are for rapid thinking and personal iteration.
- Shared notes should remain stable project guidance.

## Change Hygiene

When updating notes:

1. Preserve useful existing context.
2. Prefer appending or section edits over full rewrites.
3. Keep wording concrete (what, where, next).
4. Remove stale guidance that conflicts with current workflow.

Why:
- Notes should stay accurate, compact, and easy to trust.
