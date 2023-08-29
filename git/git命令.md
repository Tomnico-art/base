## git基本操作
### 切出dev分支
git checkout -b dev
### 添加文件
git add 文件名
### 提交
git commit -m "提交信息"
### 切回主分支
git checkout main
### 合并
git merge dev
git push


## git回退
### 查看git日志
git log
### 恢复历史版本
git reset --hard [你的commit id]
### 推送到GitHub远程仓库
git push -f


## git修改
### git 放弃所有修改
git checkout .
### 放弃某个文件的修改
git checkout -- filepathname

## git添加
### git add 文件夹/ 添加整个文件夹及内容
### git add *.文件类型 添加目录中所有此文件类型的文件