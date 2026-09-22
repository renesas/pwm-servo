# GitLab to GitHub Repository Mirroring  
 
Renesas Developers may internally use GitLab for Development. However, for publication to external audiences, GitHub is the preferred platform. 
In this case, mirroring the [orphan branch](https://git-scm.com/docs/git-checkout/2.14.6#Documentation/git-checkout.txt---orphannewbranch) `release` becomes a highly desirable feature.
GitLab can automatically mirror a repository to GitHub by pushing commits, branches, and tags whenever changes are made to the GitLab repository.
  

## Prerequisites  

- A GitLab repository that will act as the source. 
- A GitHub repository that will act as the destination.  
- A GitHub Personal Access Token (PAT) with repository access.  
---  

## Step 1: Create an Empty GitHub Repository  

1. Create a new repository in GitHub.  
2. Leave the repository completely empty:  
- Do **not** add a README.  
- Do **not** add a license.  
- Do **not** add a `.gitignore` file.  
  

> **Important:** The destination repository must be empty before the initial mirror operation.  

---  
## Step 2: Create a GitHub Personal Access Token  

GitLab uses a Personal Access Token (PAT) to authenticate to GitHub.  

1. In GitHub, navigate to:  

```text  
Settings → Developer Settings → Personal Access Tokens  
```  
2. Select **Tokens (classic)**.  
3. Click **Generate new token (classic)**.  
4. Enter a descriptive name such as:  

```text  
GitLab Mirror Token  
```  
5. Select the required repository permissions.  
- For a private repository, the `repo` scope is typically required.  
5. Generate the token.  
6. Copy and save the token immediately.  

> **Important:** GitHub only displays the token once.  

---

## Step 3: Configure Repository Mirroring in GitLab  
1. Open the GitLab project.  
2. Navigate to:  
```text  
Settings → Repository  
```  
3. Expand the **Mirroring repositories** section.  
4. Configure the mirror.  

### Mirror Settings  

| Setting               | Value                                                                              |     |
| --------------------- | ---------------------------------------------------------------------------------- | --- |
| Git Repository URL    | `https://<your-github-username>github.com/<your-github-username>/<repository>.git` |     |
| Mirror Direction      | `Push`                                                                             |     |
| Authentication Method | `Password`                                                                         |     |
| Username              | GitHub username                                                                    |     |
| Password              | GitHub Personal Access Token                                                       |     |
| Mirror Branches       | Mirror specific branches (Enter name of branch `release`)                          |     |

**Example:**  

```text  

https://renesasae@github.com/renesas/sbb-name.git  

```  
5. Click **Mirror Repository**.  

---  

## Step 4: Verify the Mirror  

1. In the **Mirroring repositories** section, verify that the new mirror appears in the list.  
2. Click **Update now** (the circular arrows icon) to trigger the first synchronization.  
3. Open the GitHub repository and refresh the page.  


You should see:  

- All commits  
- All branches  
- All tags  
- Complete repository history  

---  
## Troubleshooting  
### Authentication Failed  

Verify:  
- GitHub username is correct.  
- Personal Access Token is valid.  
- Required repository permissions have been granted.  

### Host Key Verification Failure  

If using SSH mirroring instead of HTTPS, ensure the GitHub host key has been accepted by GitLab.  
### Push Rejected  

Verify:  
- The GitHub repository is empty.  
- No conflicting commits exist in the target repository.  

### Git LFS Content Not Mirrored  
If your project uses Git LFS:  
- Confirm Git LFS is enabled on both GitLab and GitHub.  
- Perform an initial LFS migration if required.  
---  
## References  
- [GitLab Repository Mirroring Documentation](https://docs.gitlab.com/user/project/repository/mirror/)  
- [GitLab Push Mirroring Documentation](https://docs.gitlab.com/user/project/repository/mirror/push/)  
- [StackOverflow: Mirroring from GitLab to GitHub](https://stackoverflow.com/questions/30268549/mirroring-from-gitlab-to-github)  
---  

## Notes  

- Mirroring is **one-way** when configured as a **Push Mirror**.  
- Changes made directly in GitHub will **not** be replicated back to GitLab.  
- GitLab remains the source of truth and GitHub becomes a synchronized copy.