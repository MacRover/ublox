import os

import ament_index_python.packages
import launch
import launch_ros.actions


def generate_launch_description():
    config_directory = os.path.join(
        ament_index_python.packages.get_package_share_directory('ublox_gps'),
        'config')

    params_0 = os.path.join(config_directory, 'zed_f9p_rover.yaml')
    ublox_gps_node_0 = launch_ros.actions.Node(package='ublox_gps',
                                             executable='ublox_gps_node',
                                             name="ublox_gps_node_rover_0",
                                             output='both',
                                             parameters=[params_0],
                                             remappings=[
                                                ('/ublox_gps_node_rover_0/fix', '/rover/fix'),
                                                ('/ublox_gps_node_rover_0/fix_velocity', '/rover/fix_velocity'),
                                             ])

    params_1 = os.path.join(config_directory, 'zed_f9p_moving_base.yaml')
    ublox_gps_node_1 = launch_ros.actions.Node(package='ublox_gps',
                                             executable='ublox_gps_node',
                                             name="ublox_gps_node_rover_1",
                                             output='both',
                                             parameters=[params_1],
                                             remappings=[
                                                ('/ublox_gps_node_rover_1/fix', '/moving_base/fix'),
                                                ('/ublox_gps_node_rover_1/fix_velocity', '/moving_base/fix_velocity'),
                                             ])

    return launch.LaunchDescription([ublox_gps_node_0, 
                                     ublox_gps_node_1,

                                     launch.actions.RegisterEventHandler(
                                         event_handler=launch.event_handlers.OnProcessExit(
                                             target_action=ublox_gps_node_0,
                                             on_exit=[launch.actions.EmitEvent(
                                                 event=launch.events.Shutdown())],
                                         )),

                                     launch.actions.RegisterEventHandler(
                                         event_handler=launch.event_handlers.OnProcessExit(
                                             target_action=ublox_gps_node_1,
                                             on_exit=[launch.actions.EmitEvent(
                                                 event=launch.events.Shutdown())],
                                         )),

                                     ])