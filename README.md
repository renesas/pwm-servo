# Overview

This repository is a collection of reusable software made available for development with Renesas Microcontrollers.

To make your reusable software component visible in this repository see section below on [Contributions](README.md#-Contributions).

## Minumum requirements for reusable software

Each submodule referenced by this repository is a repository with the following contents, at minimum, at the root folder level.

1. A `src` folder which contains the reusable code.
2. A `docs` folder which contains documentation explaining what the reusable code does and how to integrate it into your application.
3. An `examples/vscode` folder which contains vscode + cmake projects which will produce binaries for supported targets.
4. A `metadata.r365.xml` which describing how above items should be consumed by Renesas365.

Feel free to clone this repo and initialize some existing submodules for reference.


# Contributions

Once you have met the [minimum requirements for reusable software](README.md#minumum-requirements-for-reusable-software), follow the guidelines below to contribute your New Reusable Software Component as a Git Submodule.

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

3. Perform a Git pull of the repo
      ```bash
   git pull origin main
   ```

4. Add the repository as a Git submodule:

   ```bash
   git submodule add <repository-url> <submodule-path>
   ```

5. Initialize and update the submodule:

   ```bash
   git submodule update --init <submodule-name>
   ```

6. Check out the selected release tag within the submodule:

   ```bash
   cd <submodule-path>
   git checkout <tag>
   cd ..
   ```

7. Commit the updated submodule reference in the **xplore** repository to pin the submodule to the selected tag:

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


# Resources & Support

## Feedback & Support

- [Renesas Wireless Connectivity Forum](https://community.renesas.com/wireles-connectivity)
- [Contact Technical Support](https://www.renesas.com/eu/en/support?nid=1564826&issue_type=technical)
- [Contact a Sales Representative](https://www.renesas.com/eu/en/buy-sample/locations)


## Renesas General Reference(s)

| Document | Description |
|---|---|
| [Renesas365](https://www.renesas.com/renesas365) | Discover, Select, and Develop MCU‑based Systems in One Connected Workflow |
| [xplore repo FAQ](docs/faqs.md) | Anwers to Frequently Asked Questions when working with this repository. |
| [Renesas VS Code Extensions User Guide](https://tool-support.renesas.com/e2studio/vscode/docs/index.html) | User Guide to support the development of Renesas C/C++ Projects in DA, RA, R-Car, RH850, RISC-V MCU, RL78, RX, RZ device families. |
| [Renesas RA FSP Documentation](https://renesas.github.io/fsp/) | FSP API reference for all modules used |
| [e² studio Renesas](https://www.renesas.com/en/software-tool/e2-studio?srsltid=AfmBOorTMc82ySC1OUrEN8SZbrQK2qXPYpFT_VatUYLmZMBeViM4bFTS) | e² studio user guide and tool page |