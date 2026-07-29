# Overview

This repository is a collection of reusable software made available for development with Renesas Microcontrollers.

To make your reusable software component visible in this repository see section below on [Contributions](#-Contributions).


# Resources & Support

## Feedback & Support

- [Renesas Wireless Connectivity Forum](https://community.renesas.com/wireles-connectivity)
- [Contact Technical Support](https://www.renesas.com/eu/en/support?nid=1564826&issue_type=technical)
- [Contact a Sales Representative](https://www.renesas.com/eu/en/buy-sample/locations)


## Renesas General Reference(s)

| Document | Description |
|---|---|
| [e² studio Renesas](https://www.renesas.com/en/software-tool/e2-studio?srsltid=AfmBOorTMc82ySC1OUrEN8SZbrQK2qXPYpFT_VatUYLmZMBeViM4bFTS) | e² studio user guide and tool page |
| [Renesas FSP Documentation](https://renesas.github.io/fsp/) | FSP API reference for all modules used |


# Contributions

Below are the guidelines for contributing a New Reusable Software Component as a Git Submodule.

## Prerequisites

1. Create a Personal Access Token (PAT) for your repository with the required permissions:
   - TBD

2. Clone or fork the **xplore** repository to your local machine.
   - If you cloned the repository directly, create a feature branch for your changes.
   - If you forked the repository, create the changes in your fork and submit a pull request from the fork.

## Adding a Submodule

1. Identify the repository that will be shared through **xplore**.

2. Select the release tag that should be exposed to users.
   - Only approved and validated release tags should be used.

3. Add the repository as a Git submodule:

   ```bash
   git submodule add <repository-url> <submodule-path>
   ```

4. Initialize and update the submodule:

   ```bash
   git submodule update --init
   ```

5. Check out the selected release tag within the submodule:

   ```bash
   cd <submodule-path>
   git checkout <tag>
   cd ..
   ```

6. Commit the updated submodule reference in the **xplore** repository to pin the submodule to the selected tag:

   ```bash
   git add <submodule-path>
   git commit -m "Add <submodule-name> at <tag>"
   ```

## Submitting Changes

1. Push your branch to the remote repository.

2. Submit a pull request containing:
   - The new submodule entry.
   - The pinned submodule revision corresponding to the approved tag.
   - A brief description of the repository and selected release tag.

3. Wait for review and approval before merging.

## Terminology Notes

- Use **release tag** instead of only **tag** to clarify the intent.
- Git records the submodule's commit SHA, not the tag itself. Committing the updated submodule reference pins the parent repository to the commit associated with the selected release tag.
- The clone and fork workflows differ slightly, so contributors should follow the branch and pull request process appropriate for their access level.
