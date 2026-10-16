# Overview

This file is a collection of frequently asked questions to help everyone working with the xplore repository.

# FAQs

## I care only about a few submodules in this repo. How do I limit the scope of this repo?

If you only need to work with a subset of the repository, you do not need to clone and initialize every submodule.

Clone the repository without recursively fetching submodules:

```bash
git clone <repo-url>
cd <repo-name>
```

Then initialize only the submodules you care about:

```bash
git submodule update --init path/to/submodule1
git submodule update --init path/to/submodule2
```

You can initialize multiple submodules in a single command:

```bash
git submodule update --init \
    path/to/submodule1 \
    path/to/submodule2
```

When pulling future changes, limit submodule updates to the same set:

```bash
git submodule update --remote path/to/submodule1
git submodule update --remote path/to/submodule2
```

This approach reduces:

- Clone time
- Network bandwidth
- Disk usage
- Repository complexity during development

If you later need additional components, simply initialize the corresponding submodule on demand:

```bash
git submodule update --init path/to/new-submodule
```

> **Tip:** Refer to the `.gitmodules` file in the repository root to see the complete list of available submodules and their paths.

## I don't want to distribute all of the code in my main branch. What are my options?

If your repository contains internal development assets, proprietary tooling, work-in-progress components, or other content that should not be distributed externally, you do not have to publish your main branch.

A common approach is to create a dedicated **orphan branch** (typically named `release`) that contains only the content you want to distribute.

An orphan branch has no parent history and starts as a completely independent branch. This allows you to:

- Publish only selected files and submodules.
- Exclude internal development infrastructure.
- Remove unwanted history from distributed releases.
- Maintain a clean separation between internal development and external publication.

A typical workflow looks like this:

```text
main
 ├── Internal tools
 ├── Development scripts
 ├── Experimental code
 ├── Private submodules
 └── Product source

release (orphan branch)
 ├── Public documentation
 ├── Approved source code
 ├── Approved projects
 └── metadata files
```

This enables your team to continue using `main` as the primary development branch while distributing only the curated contents of `release`.

### Publishing the Release Branch

If your development repository is hosted in GitLab and you want to publish releases to GitHub, you can configure GitLab to mirror only the `release` branch.

Benefits of this approach include:

- GitLab remains the source of truth.
- GitHub receives only the content intended for external consumption.
- Updates are synchronized automatically.
- Internal branches and development history remain private.

For detailed instructions on configuring repository mirroring, including GitHub Personal Access Tokens, GitLab mirror settings, and branch-specific mirroring, see [mirrors.md](./mirrors.md).

> **Recommended Practice:** Use an orphan `release` branch to curate publishable content, then mirror only that branch to external repositories. This provides a clear separation between internal development and externally distributed source code.

## How do I replace an existing submodule with a different repository?

Occasionally a component may be moved, renamed, consolidated into a different repository, or superseded by a newer implementation. In these situations, the existing submodule must be removed and replaced with a new one.

Typical reasons include:

- Migrating from a legacy repository to a maintained replacement.
- Consolidating multiple repositories into a single solution.
- Renaming a repository while preserving history.
- Switching to a different implementation of the same feature.
- Adopting a standardized Renesas component in place of a project-specific fork.

A typical migration workflow is:

```bash
# First, create an update branch from Main of the Repo to use for the Merge Request: for example, mr-update

# Clone the repository
git clone <old-repository-url>
cd <repository-directory>

# Create a local update branch based on main
git switch -c mr-update

# Verify branch
git status

# Remove existing submodule
git rm ./old-submodule
git commit -m "Remove old submodule"

# Add replacement submodule (from new-repository-url)
git submodule add <new-repository-url> ./new-submodule

# Pin replacement submodule to known-good commit
cd ./new-submodule
git checkout <commit-hash>
cd ..

# Record the replacement submodule
git add .gitmodules ./new-submodule
git commit -m "Add new submodule and pin version"

# Publish branch
git push origin mr-update

# Create Merge Request:
# mr-update -> main
#
# Assign a reviewer with permission to merge the MR
```

If you run into remote issues you can try
```bash
git pull --rebase origin main
git push origin main
```

### When should I use this workflow?

Use this workflow when the repository structure itself is changing. For example:

- Replacing `stdio-uart` with `stdio`.
- Migrating from an internal repository to a public repository.
- Moving from a product-specific component to a shared Renesas solution.
- Changing the local directory name associated with a submodule.

### When should I NOT use this workflow?

Do **not** use this workflow if you simply want to update an existing submodule to a newer version.

For normal submodule updates, update the submodule reference instead:

```bash
cd ./existing-submodule
git fetch
git checkout <new-commit>
cd ..

git add ./existing-submodule
git commit -m "Update submodule reference"
```

This keeps the existing submodule definition intact and only changes the version being referenced.

> **Recommended Practice:** Pin new submodules to a specific commit rather than tracking a moving branch. This ensures reproducible builds and prevents unexpected changes when upstream repositories are updated.


## How do I discover what each submodule does?


## How do I discover which Renesas microcontroller products are supported by each submodule?


## I don't have a metadata.r365.xml file. How can I create one?


## 