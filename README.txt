To upload files to this repository using Ubuntu 

1.
	$ git add FILE.EXT

# Adds the file to your local repository and stages it for commit.
 To unstage a file, use 'git reset HEAD YOUR-FILE'.

2.
	$ git commit -m "Add existing file"

# Commits the tracked changes and prepares them to be pushed to a remote repository. 
To remove this commit and modify the file, use 'git reset --soft HEAD~1' and commit and add the file again.

3.
	$ git push origin your-branch

# Pushes the changes in your local repository up to the remote repository you specified as the origin


To get files not in local repository

	$ git pull origin
	$ git pull origin master
