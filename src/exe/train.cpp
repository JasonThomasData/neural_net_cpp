#include "../network/network.h"
#include "../classifier/classifier.h"
#include "../trainer/trainer.h"
#include <vector>
#include <iostream>

double get_average_error(std::vector<double> all_total_errors)
{
    double sum = 0.0;
    for(auto& total_error: all_total_errors)
    {
        sum += total_error;
    }
    double average = sum / all_total_errors.size();
    return average;
}


void all_docs(Network& network, Classifier& classifier, Trainer& trainer)
{

    std::vector<double> all_total_errors;

    /* Document 1 */

    std::vector<double> new_inputs_1;
    double val_1 = 0.0;
    double val_2 = 0.0;
    double val_3 = 0.0;
    new_inputs_1.emplace_back(val_1);
    new_inputs_1.emplace_back(val_2);
    new_inputs_1.emplace_back(val_3);
    classifier.set_input_values(new_inputs_1);
    classifier.classify();

    std::vector<double> new_targets_1;
    double target_1 = 0.0;
    new_targets_1.emplace_back(target_1);
    trainer.set_target_values(new_targets_1);
    trainer.train();
 
    double total_error = trainer.calculate_total_error(network.output_layer);
    all_total_errors.emplace_back(total_error);

    /* Document 2 */
    std::vector<double> new_inputs_2;
    val_1 = 0.0;
    val_2 = 0.0;
    val_3 = 1.0;
    new_inputs_2.emplace_back(val_1);
    new_inputs_2.emplace_back(val_2);
    new_inputs_2.emplace_back(val_3);
    classifier.set_input_values(new_inputs_2);
    classifier.classify();

    std::vector<double> new_targets_2;
    target_1 = 0.1;
    new_targets_2.emplace_back(target_1);
    trainer.set_target_values(new_targets_2);
    trainer.train();

    total_error = trainer.calculate_total_error(network.output_layer);
    all_total_errors.emplace_back(total_error);

    /* Document 3 */
    std::vector<double> new_inputs_3;
    val_1 = 0.0;
    val_2 = 1.0;
    val_3 = 0.0;
    new_inputs_3.emplace_back(val_1);
    new_inputs_3.emplace_back(val_2);
    new_inputs_3.emplace_back(val_3);
    classifier.set_input_values(new_inputs_3);
    classifier.classify();

    std::vector<double> new_targets_3;
    target_1 = 0.2;
    new_targets_3.emplace_back(target_1);
    trainer.set_target_values(new_targets_3);
    trainer.train();

    total_error = trainer.calculate_total_error(network.output_layer);
    all_total_errors.emplace_back(total_error);

    /* Document 4 */
    std::vector<double> new_inputs_4;
    val_1 = 0.0;
    val_2 = 1.0;
    val_3 = 1.0;
    new_inputs_4.emplace_back(val_1);
    new_inputs_4.emplace_back(val_2);
    new_inputs_4.emplace_back(val_3);
    classifier.set_input_values(new_inputs_4);
    classifier.classify();

    std::vector<double> new_targets_4;
    target_1 = 0.3;
    new_targets_4.emplace_back(target_1);
    trainer.set_target_values(new_targets_4);
    trainer.train();

    total_error = trainer.calculate_total_error(network.output_layer);
    all_total_errors.emplace_back(total_error);

    /* Document 5 */
    std::vector<double> new_inputs_5;
    val_1 = 1.0;
    val_2 = 0.0;
    val_3 = 0.0;
    new_inputs_5.emplace_back(val_1);
    new_inputs_5.emplace_back(val_2);
    new_inputs_5.emplace_back(val_3);
    classifier.set_input_values(new_inputs_5);
    classifier.classify();

    std::vector<double> new_targets_5;
    target_1 = 0.4;
    new_targets_5.emplace_back(target_1);
    trainer.set_target_values(new_targets_5);
    trainer.train();

    total_error = trainer.calculate_total_error(network.output_layer);
    all_total_errors.emplace_back(total_error);

    /* Document 6 */
    std::vector<double> new_inputs_6;
    val_1 = 1.0;
    val_2 = 0.0;
    val_3 = 1.0;
    new_inputs_6.emplace_back(val_1);
    new_inputs_6.emplace_back(val_2);
    new_inputs_6.emplace_back(val_3);
    classifier.set_input_values(new_inputs_6);
    classifier.classify();

    std::vector<double> new_targets_6;
    target_1 = 0.5;
    new_targets_6.emplace_back(target_1);
    trainer.set_target_values(new_targets_6);
    trainer.train();

    total_error = trainer.calculate_total_error(network.output_layer);
    all_total_errors.emplace_back(total_error);

    /* Document 7 */
    std::vector<double> new_inputs_7;
    val_1 = 1.0;
    val_2 = 1.0;
    val_3 = 0.0;
    new_inputs_7.emplace_back(val_1);
    new_inputs_7.emplace_back(val_2);
    new_inputs_7.emplace_back(val_3);
    classifier.set_input_values(new_inputs_7);
    classifier.classify();

    std::vector<double> new_targets_7;
    target_1 = 0.6;
    new_targets_7.emplace_back(target_1);
    trainer.set_target_values(new_targets_7);
    trainer.train();

    total_error = trainer.calculate_total_error(network.output_layer);
    all_total_errors.emplace_back(total_error);

    trainer.epoch += 1;
    network.epoch_average_total_error = get_average_error(all_total_errors);
    if(trainer.epoch % 500 == 0)
    {
        std::cout<< trainer.epoch<<", "<< network.epoch_average_total_error<< std::endl;
    }

}

int main()
{
    Network network(3,30,1);
    Classifier classifier(network);
    double learning_rate = 0.25;
    Trainer trainer(network, learning_rate);

    double total_target_error = 0.0005;

    std::cout<< "Epoch"<<", "<< "epoch_average_total_error"<< std::endl;
    all_docs(network, classifier, trainer);

    while(network.epoch_average_total_error > total_target_error)
    {
        all_docs(network, classifier, trainer);
    }

    return 0;
}
