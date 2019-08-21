#开始ovs
export PATH=$PATH:/usr/local/share/openvswitch/scripts
sudo ovs-ctl stop
sudo ovs-ctl start
#配flow
sudo ovs-vsctl set interface dpdkp0 ofport_request=1 
sudo ovs-vsctl set interface "dpdkvhostuser0" ofport_request=2 
sudo ovs-vsctl set interface "dpdkvhostuser1" ofport_request=3 
sudo ovs-ofctl add-flow ovsbr0 in_port=1,action=output:2 
sudo ovs-ofctl add-flow ovsbr0 in_port=2,action=output:3
sudo ovs-ofctl add-flow ovsbr0 in_port=3,action=output:1

sleep 3
sudo ovs-vsctl show
sudo ovs-appctl dpif/show 
