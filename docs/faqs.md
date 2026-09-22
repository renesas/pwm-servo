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

For detailed instructions on configuring repository mirroring, including GitHub Personal Access Tokens, GitLab mirror settings, and branch-specific mirroring, see [mirrors.md](mirror.md).

> **Recommended Practice:** Use an orphan `release` branch to curate publishable content, then mirror only that branch to external repositories. This provides a clear separation between internal development and externally distributed source code.

## How do I discover what each submodule does?


## How do I discover which Renesas microcontroller products are supported by each submodule?


## I don't have a metadata.r365.xml file. How can I create one?


## 