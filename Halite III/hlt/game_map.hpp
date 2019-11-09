#pragma once

#include "types.hpp"
#include "map_cell.hpp"

#include <vector>

namespace hlt {
    struct GameMap {
        int width;
        int height;
        std::vector<std::vector<MapCell>> cells;

        MapCell* at(const Position& position) {
            Position normalized = normalize(position);
            return &cells[normalized.y][normalized.x];
        }

        MapCell* at(const Entity& entity) {
            return at(entity.position);
        }

        MapCell* at(const Entity* entity) {
            return at(entity->position);
        }

        MapCell* at(const std::shared_ptr<Entity>& entity) {
            return at(entity->position);
        }

        int calculate_distance(const Position& source, const Position& target) {
            const auto& normalized_source = normalize(source);
            const auto& normalized_target = normalize(target);

            const int dx = std::abs(normalized_source.x - normalized_target.x);
            const int dy = std::abs(normalized_source.y - normalized_target.y);

            const int toroidal_dx = std::min(dx, width - dx);
            const int toroidal_dy = std::min(dy, height - dy);

            return toroidal_dx + toroidal_dy;
        }

        Position normalize(const Position& position) {
            const int x = ((position.x % width) + width) % width;
            const int y = ((position.y % height) + height) % height;
            return { x, y };
        }

        std::vector<Direction> get_unsafe_moves(const Position& source, const Position& destination) {
            const auto& normalized_source = normalize(source);
            const auto& normalized_destination = normalize(destination);

            const int dx = std::abs(normalized_source.x - normalized_destination.x);
            const int dy = std::abs(normalized_source.y - normalized_destination.y);
            const int wrapped_dx = width - dx;
            const int wrapped_dy = height - dy;

            std::vector<Direction> possible_moves;

            if (normalized_source.x < normalized_destination.x) {
                possible_moves.push_back(dx > wrapped_dx ? Direction::WEST : Direction::EAST);
            } else if (normalized_source.x > normalized_destination.x) {
                possible_moves.push_back(dx < wrapped_dx ? Direction::WEST : Direction::EAST);
            }

            if (normalized_source.y < normalized_destination.y) {
                possible_moves.push_back(dy > wrapped_dy ? Direction::NORTH : Direction::SOUTH);
            } else if (normalized_source.y > normalized_destination.y) {
                possible_moves.push_back(dy < wrapped_dy ? Direction::NORTH : Direction::SOUTH);
            }

            return possible_moves;
        }
        std::vector<Direction> get_moves(const Position& source, const Position& destination) {
          const auto& normalized_source = normalize(source);
          const auto& normalized_destination = normalize(destination);

          int dx = std::abs(normalized_source.x - normalized_destination.x);
          int dy = std::abs(normalized_source.y - normalized_destination.y);

          int wrapped_dx = width - dx;
          int wrapped_dy = height - dy;
          std::vector<Direction> possible_moves;

          if(normalized_source.x < normalized_destination.x) {
              if(dx > wrapped_dx) {
                for(int i = 0; i < wrapped_dx; i++) {
                  possible_moves.push_back(Direction::WEST);
                }
              } else {
                for(int i = 0; i < dx; i++) {
                  possible_moves.push_back(Direction::EAST);
                }
              }
          } else {
            if(normalized_source.x > normalized_destination.x) {
              if(dx < wrapped_dx) {
                for(int i = 0; i < dx; i++) {
                  possible_moves.push_back(Direction::WEST);
                }
              } else {
                for(int i = 0; i < wrapped_dx; i++) {
                  possible_moves.push_back(Direction::EAST);
                }
              }
            }
          }

          if(normalized_source.y < normalized_destination.y) {
              if(dy > wrapped_dy) {
                for(int i = 0; i < wrapped_dy; i++) {
                  possible_moves.push_back(Direction::NORTH);
                }
              } else {
                for(int i = 0; i < dy; i++) {
                  possible_moves.push_back(Direction::SOUTH);
                }
              }
          } else {
            if(normalized_source.y> normalized_destination.y) {
              if(dy < wrapped_dy) {
                for(int i = 0; i < dy; i++) {
                  possible_moves.push_back(Direction::NORTH);
                }
              } else {
                for(int i = 0; i < wrapped_dy; i++) {
                  possible_moves.push_back(Direction::SOUTH);
                }
              }
            }
          }
          return possible_moves;
        };

        Direction naive_navigate(std::shared_ptr<Ship> ship, const Position& destination) {
            // get_unsafe_moves normalizes for us
            for (auto direction : get_unsafe_moves(ship->position, destination)) {
                Position target_pos = ship->position.directional_offset(direction);
                if (!at(target_pos)->is_occupied()) {
                //    at(target_pos)->mark_unsafe(ship);
                    return direction;
                }
            }

            return Direction::STILL;
        }

        void _update();
        static std::unique_ptr<GameMap> _generate();
    };
}
