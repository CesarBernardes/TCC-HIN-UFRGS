***Repository for TCC studies on heavy ion collisions at IF-UFRGS

To contribute to this repository (also known as repo), please, follow the steps:

1) To be done just once (forking, i.e. creates a replica of the repo):

   To do this, 

       1.1 Go to your web browser, navigate to GitHub and log in

       1.2 Navigate to the repo: https://github.com/CesarBernardes/TCC-HIN-UFRGS

       1.3 On the top-right corner, click on the Fork button. This button will automatically create a copy of that repository in your account

       1.4 Once forked, you should now see the same repository in your repository list 

2) All the time you have a change to do, "commit" your changes to your personal forked repo and "push" that code to the github repo

   It is possible to commit changes directly in the web browser, but is better do it locally, then test it before pushing. To change locally:

       2.1 "Clone" the entire repo to your local computer with git (just need to do once). Assuming you are in your forked repo on github, click on the "Code" (green button). Then copy the URL. In the command line in your computer, to do: "git clone <URL>"

       2.2 Now you can change your files and commit your changes. For example, suppose you want to change a file called "test.txt":
             
          Edit the file; Then do: < git add test.txt >, then < git commit -m "modified test.txt file" >, then push changes to GitHub repo with the git push command: < git push >
          
3) Submit a Pull Request (also known as PR) to the repo

      Follwoing the procedures above, now you have a copy of the GitHub repo including your changes (in the forked repo) you want to submit to the "original" repo. For this, please, do a pull request:

     3.1 Go to your forked repo on Github

     3.2 Click on "Pull Resquests" and the "New pull request" 

     3.3 On the pull request page, you’ll see the two repos that will be compared and each commit you’re requesting to merge into the original GitHub repo. Please, click on "Create pull request"

     3.4 Provide a title to the pull request and click on "Create pull request" 
       
4) Then we will review your changes and approve them

5) After approved, they will be merged into the "main" branch of the original repo 

6) Now, suppose you did all the steps above and some days after other people update the original repo, then you want to get your local code and forked repo updated in order to apply further changes. For this, please, do the following:

     6.1 Add the "remote" (Remotes are like nicknames for the URLs of repositories), call it "remoteName":

           git remote add remoteName https://github.com/CesarBernardes/IC-HIN-UFRGS.git

     6.2 Fetch all the branches of that remote into remote-tracking branches

           git fetch remoteName

     6.3 Make sure that you're on your "main" branch:

           git checkout main

     6.4 Rewrite your main branch so that any commits of yours that aren't already in "remoteName/main" are replayed on top of that other branch:

           git rebase remoteName/main

     6.5 If you've rebased your branch onto "remoteName/main" you may need to force the push in order to push it to your own forked repository on GitHub. You'd do that with:

           git push -f origin main

      After that you are ready to prepare new PRs on top of "main" branch of original repo. :-)  

