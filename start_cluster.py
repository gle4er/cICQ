#!/usr/bin/python

from subprocess import Popen

class Server:
    def __init__(self, ip, client_port, cluster_port):
        self.ip = ip
        self.client_port = client_port
        self.cluster_port = cluster_port

cluster_list = [Server('127.0.0.1', str(5000 + i), str(9000 + i)) for i in range(2)]

processes = []
for number in range(len(cluster_list)):
    curr_server = cluster_list[number]
    curr_list = cluster_list.copy()
    curr_list.pop(number)
    cluster_hosts = ''
    for host in curr_list:
        cluster_hosts += host.ip + ':' + host.cluster_port + ','
    cluster_hosts = cluster_hosts[:-1]
    print(f'Start {number} server')
    proc = Popen(['./cicq_server', curr_server.client_port, curr_server.cluster_port, cluster_hosts])
    processes.append(proc)

for proc in processes:
    proc.wait()
