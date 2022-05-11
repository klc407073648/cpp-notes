
#  Kubernetes 命令学习

## 个人总结


k8s命令如下:

```
kubectl get pods

kubectl delete pod startquitcycle-demo

kubectl create -f lifecyle.yaml
kubectl exec  lifecycle-demo -it -- /bin/bash

kubectl delete pod lifecycle-demo

kubectl delete pods --all

kubectl delete rc mysql
kubectl delete rc myweb

docker rm $(docker ps -q -f status=exited)
```
